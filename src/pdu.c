#include <byteswap.h>
#include <string.h>
#include "pdu.h"

typedef struct pdu_tree {
    pdu_node_t nodes[0xFFFF];
    uint32_t   cursor;
} pdu_tree_t;

static pdu_tree_t           pdu_tree;
static dict_node_t         *dict_nodes;

#define BITSET_LAST(k,n) ((k) & ((1<<(n))-1))
#define BITSET_MID(k,m,n) BITSET_LAST((k)>>(m),((n)-(m)))

void
pdu_dict_register(dict_node_t *nodes)
{
    dict_nodes = nodes;
}

pdu_node_t *
pdu_node_mkpacket(char *data, uint16_t size, void *context)
{
    memset(pdu_tree.nodes, 0, sizeof(pdu_tree.nodes[0]) * pdu_tree.cursor);
    pdu_tree.cursor = 0;

    pdu_node_t *pnode = &pdu_tree.nodes[pdu_tree.cursor++];

    pnode->name        = "PDU";
    pnode->description = "";
    pnode->type        = DICT_NTYPE_PDU;
    pnode->visibility  = true;
    pnode->val.type    = DICT_DTYPE_BYTES;
    pnode->val.data    = data;
    pnode->val.size    = size;

    return pnode;
}


static pdu_node_t *
pdu_node_mk__    (char *name, pdu_node_t *parent, char *data, uint16_t size)
{
    dict_node_t *dnode = dict_nodes;
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
            pnode->description = dnode->description;
            pnode->type        = dnode->nodetype;
            pnode->visibility  = dnode->visibility;
            pnode->val.type    = dnode->datatype;
            pnode->val.data    = data;
            pnode->val.size    = size;

            if (dnode->datatype == DICT_DTYPE_HEX8) {
                pnode->val.size = 1;
            } else if (dnode->datatype == DICT_DTYPE_HEX16) {
                pnode->val.size = 2;
            } else if (dnode->datatype == DICT_DTYPE_HEX24) {
                pnode->val.size = 4;
            } else if (dnode->datatype == DICT_DTYPE_HEX32) {
                pnode->val.size = 4;
            } else if (dnode->datatype == DICT_DTYPE_UINT8) {
                pnode->val.size = 1;
            } else if (dnode->datatype == DICT_DTYPE_UINT16) {
                pnode->val.size = 2;
            } else if (dnode->datatype == DICT_DTYPE_UINT24) {
                pnode->val.size = 4;
            } else if (dnode->datatype == DICT_DTYPE_UINT32) {
                pnode->val.size = 4;
            }

            return pnode;
        }
    }
    return NULL;
}

pdu_node_t *
pdu_node_mk      (char *name, pdu_node_t *parent, char *data, uint16_t size)
{
    pdu_node_t *node = pdu_node_mk__(name, parent, data, size);
    if (!node) {
        return NULL;
    }
    return node;
}


pdu_node_t *
pdu_node_mkbitset(char *name, pdu_node_t *parent, char *data, uint16_t bitfrom, uint16_t bitto)
{
    pdu_node_t *node = pdu_node_mk__(name, parent, data, 0);
    if (!node) {
        return NULL;
    }
    node->val.bitfrom = bitfrom;
    node->val.bitto   = bitto;
    return node;
}

pdu_node_t *
pdu_node_get_root(void *context)
{
    return &pdu_tree.nodes[0];
}

void
pdu_node_trace(pdu_node_t *node)
{
    static int padding;

    for (int ic = 0; ic < padding; ic++) {
        fprintf(stdout, "  ");
    }
    fprintf(stdout, "%s: ", node->name);

    if (!node->val.bitfrom && !node->val.bitto) {

        if (node->val.type == DICT_DTYPE_HEX8) {
            fprintf(stdout, "%x", *(uint8_t*)node->val.data);
        } else if (node->val.type == DICT_DTYPE_HEX16) {
            fprintf(stdout, "%x", bswap_16(*(uint16_t*)node->val.data));
        } else if (node->val.type == DICT_DTYPE_HEX24) {
            fprintf(stdout, "%x", bswap_32(*(uint32_t*)node->val.data) & 0xFFFFFF);
        } else if (node->val.type == DICT_DTYPE_HEX32) {
            fprintf(stdout, "%x", bswap_32(*(uint32_t*)node->val.data));

        } else if (node->val.type == DICT_DTYPE_UINT8) {
            fprintf(stdout, "%u", *(uint8_t*)node->val.data);
        } else if (node->val.type == DICT_DTYPE_UINT16) {
            fprintf(stdout, "%u", bswap_16(*(uint16_t*)node->val.data));
        } else if (node->val.type == DICT_DTYPE_UINT24) {
            fprintf(stdout, "%u", bswap_32(*(uint32_t*)node->val.data) & 0xFFFFFF);
        } else if (node->val.type == DICT_DTYPE_UINT32) {
            fprintf(stdout, "%u", bswap_32(*(uint32_t*)node->val.data));
        }
    }

    if (node->val.bitfrom || node->val.bitto) {
        if (node->val.type == DICT_DTYPE_UINT8) {
            fprintf(stdout, "%u  ", (BITSET_MID(*((uint8_t *)node->val.data), node->val.bitfrom, node->val.bitto)));
        } else if (node->val.type == DICT_DTYPE_UINT16) {
            fprintf(stdout, "%u  ", (BITSET_MID(*((uint16_t *)node->val.data), node->val.bitfrom, node->val.bitto)));
        } else if (node->val.type == DICT_DTYPE_UINT32) {
            fprintf(stdout, "%u",   (BITSET_MID(*((uint32_t *)node->val.data), node->val.bitfrom, node->val.bitto)));
        } else if (node->val.type == DICT_DTYPE_UINT64) {
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
