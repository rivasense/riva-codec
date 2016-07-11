#include <byteswap.h>
#include <string.h>
#include "pdu.h"

typedef struct pdu_tree {
    pdu_node_t nodes[0xFFFF];
    uint32_t   cursor;
} pdu_tree_t;

static pdu_tree_t           pdu_tree;
static pdu_field_t         *pdu_dict;

#define BITSET_LAST(k,n) ((k) & ((1<<(n))-1))
#define BITSET_MID(k,m,n) BITSET_LAST((k)>>(m),((n)-(m)))

void
pdu_fields_register (pdu_field_t *fields)
{
    pdu_dict = fields;
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

    if (!node->val.bitfrom && !node->val.bitto) {

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
    }

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
    pnode->description = "";
    pnode->type        = PDU_FF_PDU;
    pnode->visibility  = true;
    pnode->val.type    = PDU_FT_BYTES;
    pnode->val.data    = data;
    pnode->val.size    = size;

    return pnode;
}

char *
pdu_node_cursor     (pdu_node_t *parent, int offset, int position)
{
    return NULL;
}




static pdu_node_t *
pdu_node_mk__    (char *name, pdu_node_t *parent, char *data, uint16_t size)
{
    pdu_field_t *dnode = pdu_dict;
    for (; dnode->name; dnode++) {
        if (strcmp(name, dnode->name) == 0) {

            pdu_node_t *pnode = &pdu_tree.nodes[pdu_tree.cursor++];
            if (!parent->child_f || !parent->child_l) {
                parent->child_f = parent->child_l = pnode;
            } else {
                parent->child_l->next = pnode;
                parent->child_l = pnode;
            }

            pnode->name        = dnode->name;
            pnode->val.data    = data;
            pnode->val.size    = size;

            if (dnode->type == PDU_FT_HEX8) {
                pnode->val.size = 1;
            } else if (dnode->type == PDU_FT_HEX16) {
                pnode->val.size = 2;
            } else if (dnode->type == PDU_FT_HEX24) {
                pnode->val.size = 4;
            } else if (dnode->type == PDU_FT_HEX32) {
                pnode->val.size = 4;
            } else if (dnode->type == PDU_FT_UINT8) {
                pnode->val.size = 1;
            } else if (dnode->type == PDU_FT_UINT16) {
                pnode->val.size = 2;
            } else if (dnode->type == PDU_FT_UINT24) {
                pnode->val.size = 4;
            } else if (dnode->type == PDU_FT_UINT32) {
                pnode->val.size = 4;
            }

            return pnode;
        }
    }
    return NULL;
}

pdu_node_t *
pdu_node_mk         (char *name, pdu_node_t *parent, ... )
{
    pdu_node_t *node = pdu_node_mk__(name, parent, NULL, 0);
    if (!node) {
        return NULL;
    }
    return node;
}

pdu_node_t *
pdu_node_mknext     (char *name, pdu_node_t *parent, ... )
{
    return NULL;
}

pdu_node_t *
pdu_node_mkdata     (char *name, pdu_node_t *parent, char *data, ... )
{
    return NULL;
}

pdu_node_t *
pdu_node_mksize     (char *name, pdu_node_t *parent, size_t *size, ... )
{
    return NULL;
}

pdu_node_t *
pdu_node_mkdatasize (char *name, pdu_node_t *parent, char *data, size_t size, ... )
{
    return NULL;
}


