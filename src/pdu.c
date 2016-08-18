#include <byteswap.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "pdu.h"
#include "pdu-idx.h"

typedef struct pdu_heap {
    pdu_node_t nodes[0xFFFF];
    uint32_t   cursor;
} pdu_heap_t;

static pdu_heap_t        pdu_heap;
static pdu_idx_t        *pdu_dict;
static pdu_field_dict_t  root_field = { .name = "PDU", .type = PDU_FT_PDU };

#define BITSET_LAST(k,n) ((k) & ((1<<(n))-1))
#define BITSET_MID(k,m,n) BITSET_LAST((k)>>(m),((n)-(m)))

void
pdu_fields_register (pdu_field_dict_t *fields)
{
    if (pdu_dict == NULL) {
        /* initialize empty dictionary */
        pdu_dict = pdu_idx_create();
        pdu_idx_insert(pdu_dict, root_field.name, &root_field);
    }

    /* for each dictionary fields .... */
    for (int ifield = 0; fields[ifield].name; ifield++) {

        pdu_field_dict_t *field = &fields[ifield];

        /* calculate mask offset/bitlen helpers */
        uint64_t mask = field->mask;
        if (mask) {
            while (!(mask & 1) ) {
                field->mask_offset++;
                mask >>= 1;
            }
            while ( mask ) {
                field->mask_bitlen++;
                mask >>= 1;
            }
        }
        /* generate description, if not set */
        if (!field->desc) {
            int lname = strlen(field->name);
            int idx = lname - 1;
            for (; (idx >= 0) && (field->name[idx] != '.'); idx--);
            if (idx >= 0) {
                field->desc = strdup(&field->name[idx + 1]);
            }
            for (idx = 0; !field->desc[idx]; idx++) {
                switch (field->desc[idx]) {
                case '_': field->desc[idx] = '-';
                }
            }
        }
        /* set field type */
        if (field->type == PDU_FT_DEFAULT) {
            field->type = PDU_FT_SECTION;
        }
        /* insert to the field index */
        int rcode = pdu_idx_insert(pdu_dict, field->name, field);
        if (rcode <= 0) {
            /* TODO: error handling here */
            fprintf(stderr, "duplication: %s\n", field->name);
        }
    }
}

pdu_node_t *
pdu_node_get_root   (void *context)
{
    return &pdu_heap.nodes[0];
}

void
pdu_node_get_value  (pdu_node_t *node, void *value)
{
    uint8_t  *u8  = value;
    uint16_t *u16 = value;
    uint32_t *u32 = value;

    switch(PDU_FTGET_BYTES(node->dict->type)) {
    case 1: *u8  = *(uint8_t*)node->val.data;
            break;
    case 2: *u16 = bswap_16(*(uint16_t*)node->val.data);
            break;
    case 3: *u32 = bswap_32(*(uint32_t*)node->val.data) >> 8;
            break;
    case 4: *u32 = bswap_32(*(uint32_t*)node->val.data);
            break;
    }

    if (node->dict->mask) {
        switch(PDU_FTGET_BYTES(node->dict->type)) {
        case 1: *u8 = (*u8 & node->dict->mask) >> node->dict->mask_offset;
                break;
        case 2: *u16 = (*u16 & node->dict->mask) >> node->dict->mask_offset;
                break;
        case 4: *u32 = (*u32 & node->dict->mask) >> node->dict->mask_offset;
                break;
        }
    }
}

void
pdu_node_trace      (pdu_node_t *node)
{
    static int padding;

    for (int ic = 0; ic < padding; ic++) {
        fprintf(stdout, "  ");
    }
    fprintf(stdout, "%s: ", node->dict->desc ? node->dict->desc : node->dict->name);

    if ((PDU_FTGET_FAMILY(node->dict->type) == PDU_FFAMILY_UINT) ||
        (PDU_FTGET_FAMILY(node->dict->type) == PDU_FFAMILY_HEX)) {

        uint64_t data = 0;

        switch(node->val.size) {
        case 1: data = *(uint8_t*)node->val.data;
                break;
        case 2: data = bswap_16(*(uint16_t*)node->val.data);
                break;
        case 3: data = bswap_32(*(uint32_t*)node->val.data) >> 8;
                break;
        case 4: data = bswap_32(*(uint32_t*)node->val.data);
                break;
        }
        if (node->dict->mask) {
            data = (data & node->dict->mask) >> node->dict->mask_offset;
        }

        char *format = (PDU_FTGET_FAMILY(node->dict->type) == PDU_FFAMILY_HEX) ? "%x" : "%u";
        fprintf(stdout, format, data);
    }

    fprintf(stdout, "\n");

    if (node->child_f) {
        padding++;
        pdu_node_trace(node->child_f);
        padding--;
    }
    if (node->next) {
        pdu_node_trace(node->next);
    }
}

pdu_node_t *
pdu_node_mkpacket   (char *data, uint16_t size, void *context)
{
    memset(pdu_heap.nodes, 0, sizeof(pdu_heap.nodes[0]) * pdu_heap.cursor);
    pdu_heap.cursor = 0;
    pdu_node_t *pnode = &pdu_heap.nodes[pdu_heap.cursor++];

    void *field_dict = NULL;
    if (pdu_idx_search(pdu_dict, "PDU", &field_dict) <= 0) {
        /* TODO: error handling here */
        fprintf(stderr, "can't find root field\n");
        exit(0);
    }
    pnode->dict     = (pdu_field_dict_t *)field_dict;
    pnode->val.data = data;
    pnode->val.size = size;

    return pnode;
}

char *
pdu_node_cursor     (pdu_node_t *node, uint16_t offset, uint16_t offtype)
{
    char *cursor = &node->val.data[node->val.cursor];

    switch (offtype) {
    case PDU_CURSOFF_BEGIN:
        node->val.cursor  = offset;
        break;
    case PDU_CURSOFF_END:
        node->val.cursor  = node->val.size - offset;
        break;
    case PDU_CURSOFF_INC:
        node->val.cursor += offset;
        break;
    case PDU_CURSOFF_DEC:
        node->val.cursor -= offset;
        break;
    }

    if (node->val.cursor > node->val.size) {
        node->val.cursor = 0;
        return NULL;
    }

    return cursor;
}

static pdu_node_t *
pdu_node_mk__    (char *name, pdu_node_t *parent, char *data, uint16_t size, bool next)
{
    void *field_dict = NULL;
    if (pdu_idx_search(pdu_dict, name, &field_dict) <= 0) {
        /* TODO: error handling here */
        fprintf(stderr, "can't find field: %s\n", name);
        exit(0);
    }

    /* node allocation */
    pdu_node_t *pnode = &pdu_heap.nodes[pdu_heap.cursor++];
    /* setup relations */
    if (!parent->child_f || !parent->child_l) {
        parent->child_f = parent->child_l = pnode;
    } else {
        parent->child_l->next = pnode;
        parent->child_l = pnode;
    }
    pnode->parent = parent;

    /* setup values */
    pnode->dict            = (pdu_field_dict_t *)field_dict;
    pnode->val.data = data ? data : &parent->val.data[parent->val.cursor];
    pnode->val.size = size ? size : pnode->dict->type & 0xF;

    if (data) {
        parent->val.cursor = data - parent->val.data;
    }
    if (next) {
        parent->val.cursor += pnode->val.size;
    }

    return pnode;
}

pdu_node_t *
pdu_node_mk         (char *name, pdu_node_t *parent, ... )
{
    pdu_node_t *node = pdu_node_mk__(name, parent, NULL, 0, false);
    return node;
}

pdu_node_t *
pdu_node_mknext     (char *name, pdu_node_t *parent, ... )
{
    pdu_node_t *node = pdu_node_mk__(name, parent, NULL, 0, true);
    return node;
}

pdu_node_t *
pdu_node_mkclone    (char *name, pdu_node_t *parent, ... )
{
    pdu_node_t *node = pdu_node_mk__(name, parent, NULL, 0, false);
    node->val = parent->val;
    node->val.cursor = 0;
    return node;
}

pdu_node_t *
pdu_node_mkdata     (char *name, pdu_node_t *parent, char *data, ... )
{
    pdu_node_t *node = pdu_node_mk__(name, parent, data, 0, true);
    return node;
}

pdu_node_t *
pdu_node_mksize     (char *name, pdu_node_t *parent, size_t size, ... )
{
    pdu_node_t *node = pdu_node_mk__(name, parent, NULL, size, true);
    return node;
}

pdu_node_t *
pdu_node_mkdatasize (char *name, pdu_node_t *parent, char *data, size_t size, ... )
{
    pdu_node_t *node = pdu_node_mk__(name, parent, data, size, true);
    return node;
}

