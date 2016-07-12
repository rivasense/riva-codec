#include <byteswap.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "pdu.h"

typedef struct pdu_attr {
    uint32_t   mask_offset;
    uint32_t   mask_bitlen;
} pdu_attr_t;

typedef struct pdu_tree {
    pdu_node_t nodes[0xFFFF];
    uint32_t   cursor;
} pdu_tree_t;

static pdu_tree_t           pdu_tree;
static pdu_field_t         *pdu_dict;
static pdu_attr_t          *pdu_dict_attrs;

#define BITSET_LAST(k,n) ((k) & ((1<<(n))-1))
#define BITSET_MID(k,m,n) BITSET_LAST((k)>>(m),((n)-(m)))

void
pdu_fields_register (pdu_field_t *fields)
{
    pdu_dict = fields;

    pdu_field_t *node  = NULL;
    int          nodes = 0;
    for (node = pdu_dict, nodes = 0; node->name; node++, nodes++);

    pdu_dict_attrs = calloc(nodes, sizeof(pdu_dict_attrs[0]));
    for (int inode = 0; inode < nodes; inode++) {
        uint64_t mask = pdu_dict[inode].mask;
        if (mask) {
            while (!(mask & 1) ) {
                pdu_dict_attrs[inode].mask_offset++;
                mask >>= 1;
            }
            while ( !mask ) {
                pdu_dict_attrs[inode].mask_bitlen++;
                mask >>= 1;
            }
        }
    }
}

pdu_node_t *
pdu_node_get_root   (void *context)
{
    return &pdu_tree.nodes[0];
}

void
pdu_node_trace      (pdu_node_t *node)
{
    static int padding;

    for (int ic = 0; ic < padding; ic++) {
        fprintf(stdout, "  ");
    }
    fprintf(stdout, "%s: ", node->name);

    if (node->val.type == PDU_FT_HEX8) {
        fprintf(stdout, "%x", *(uint8_t*)node->val.data);
    } else if (node->val.type == PDU_FT_HEX16) {
        fprintf(stdout, "%x", bswap_16(*(uint16_t*)node->val.data));
    } else if (node->val.type == PDU_FT_HEX24) {
        fprintf(stdout, "%x", bswap_32(*(uint32_t*)node->val.data)  >> 8 & 0xFFFFFF);
    } else if (node->val.type == PDU_FT_HEX32) {
        fprintf(stdout, "%x", bswap_32(*(uint32_t*)node->val.data));

    } else if (node->val.type == PDU_FT_UINT8) {
        fprintf(stdout, "%u", *(uint8_t*)node->val.data);
    } else if (node->val.type == PDU_FT_UINT16) {
        fprintf(stdout, "%u", bswap_16(*(uint16_t*)node->val.data));
    } else if (node->val.type == PDU_FT_UINT24) {
        fprintf(stdout, "%u", bswap_32(*(uint32_t*)node->val.data) & 0xFFFFFF);
    } else if (node->val.type == PDU_FT_UINT32) {
        fprintf(stdout, "%u", bswap_32(*(uint32_t*)node->val.data));
    }

#if 0
    if (!node->val.bitfrom && !node->val.bitto) {

    }
#endif
#if 0
    if (node->val.bitfrom || node->val.bitto) {
        if (node->val.type == PDU_FT_HEX8) {
            fprintf(stdout, "%x  ", (BITSET_MID(*((uint8_t *)node->val.data), node->val.bitfrom, node->val.bitto)));
        } else if (node->val.type == PDU_FT_HEX16) {
            fprintf(stdout, "%x  ", (BITSET_MID(*((uint16_t *)node->val.data), node->val.bitfrom, node->val.bitto)));
        } else if (node->val.type == PDU_FT_HEX32) {
            fprintf(stdout, "%x",   (BITSET_MID(*((uint32_t *)node->val.data), node->val.bitfrom, node->val.bitto)));
        } else if (node->val.type == PDU_FT_HEX64) {
            fprintf(stdout, "%lx",  (BITSET_MID(*((uint64_t *)node->val.data), node->val.bitfrom, node->val.bitto)));
        }

        if (node->val.type == PDU_FT_UINT8) {
            fprintf(stdout, "%u  ", (BITSET_MID(*((uint8_t *)node->val.data), node->val.bitfrom, node->val.bitto)));
        } else if (node->val.type == PDU_FT_UINT16) {
            fprintf(stdout, "%u  ", (BITSET_MID(*((uint16_t *)node->val.data), node->val.bitfrom, node->val.bitto)));
        } else if (node->val.type == PDU_FT_UINT32) {
            fprintf(stdout, "%u",   (BITSET_MID(*((uint32_t *)node->val.data), node->val.bitfrom, node->val.bitto)));
        } else if (node->val.type == PDU_FT_UINT64) {
            fprintf(stdout, "%lu",  (BITSET_MID(*((uint64_t *)node->val.data), node->val.bitfrom, node->val.bitto)));
        }
    }
#endif
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
    memset(pdu_tree.nodes, 0, sizeof(pdu_tree.nodes[0]) * pdu_tree.cursor);
    pdu_tree.cursor = 0;

    pdu_node_t *pnode = &pdu_tree.nodes[pdu_tree.cursor++];

    pnode->name        = "PDU";
    pnode->val.type    = PDU_FT_BYTES;
    pnode->val.flags   = PDU_FF_PDU;
    pnode->val.data    = data;
    pnode->val.size    = size;

    return pnode;
}

char *
pdu_node_cursor     (pdu_node_t *node, uint16_t offset, uint16_t offtype)
{
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

    return &node->val.data[node->val.cursor];
}





static pdu_node_t *
pdu_node_mk__    (char *name, pdu_node_t *parent, char *data, uint16_t size, bool next)
{
    pdu_field_t *dnode = pdu_dict;
    for (int inode = 0; dnode->name; dnode++, inode++) {
        if (strcmp(name, dnode->name) == 0) {

            pdu_node_t *pnode = &pdu_tree.nodes[pdu_tree.cursor++];
            if (!parent->child_f || !parent->child_l) {
                parent->child_f = parent->child_l = pnode;
            } else {
                parent->child_l->next = pnode;
                parent->child_l = pnode;
            }

            pnode->name            = dnode->name;
            pnode->val.type        = dnode->type;
            pnode->val.flags       = dnode->flags;
            pnode->val.mask        = dnode->mask;
            pnode->val.mask_offset = pdu_dict_attrs[inode].mask_offset;
            pnode->val.mask_bitlen = pdu_dict_attrs[inode].mask_offset;

            pnode->val.data = data ? data : &parent->val.data[parent->val.cursor];
            pnode->val.size = size ? size : dnode->type & 0xF;

            if (data) {
                parent->val.cursor = data - parent->val.data;
            }
            if (next) {
                parent->val.cursor += pnode->val.size;
            }

            return pnode;
        }
    }
    return NULL;
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

