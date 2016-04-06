#include <byteswap.h>
#include <string.h>
#include "pdu.h"

typedef struct pdu_tree {
    pdu_node_t nodes[0xFFFF];
    uint32_t   cursor;
} pdu_tree_t;

static pdu_tree_t           pdu_tree;
static dict_node_t         *dict_nodes;
static char                *__data;

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
    return &pdu_tree.nodes[pdu_tree.cursor];
}

pdu_node_t *
pdu_node_mk      (char *name, pdu_node_t *parent, char *data, uint16_t size)
{
    fprintf(stdout, "%s: ", name);

    dict_node_t *dnode = dict_nodes;
    for (; dnode->name; dnode++) {
        if (strstr(name, dnode->name)) {

            if (dnode->datatype == DICT_DTYPE_HEX8) {
                size = 1;
                fprintf(stdout, "%x", (uint8_t)*data);
            } else if (dnode->datatype == DICT_DTYPE_HEX16) {
                size = 2;
                fprintf(stdout, "%x", bswap_16((uint16_t)*data));
            } else if (dnode->datatype == DICT_DTYPE_HEX32) {
                size = 4;
                fprintf(stdout, "%x", bswap_32((uint32_t)*data));

            } else if (dnode->datatype == DICT_DTYPE_UINT8) {
                size = 1;
                fprintf(stdout, "%u", (uint8_t)*data);
            } else if (dnode->datatype == DICT_DTYPE_UINT16) {
                size = 2;
                fprintf(stdout, "%u", bswap_16((uint16_t)*data));
            } else if (dnode->datatype == DICT_DTYPE_UINT32) {
                size = 4;
                fprintf(stdout, "%u", bswap_32((uint32_t)*data));
            }

            break;
        }
    }

    fprintf(stdout, " [ ");
    for (uint16_t sz = 0; sz < size; sz++) {
        fprintf(stdout, "%02x ", data[sz] & 0xFF);
    }
    fprintf(stdout, "]\n");

    __data = data;

    return NULL;
}


pdu_node_t *
pdu_node_mkbitset(char *name, pdu_node_t *parent, char *data, uint16_t bitfrom, uint16_t bitto)
{
    fprintf(stdout, "%s: ", name);

    dict_node_t *dnode = dict_nodes;
    for (; dnode->name; dnode++) {
        if (strstr(name, dnode->name)) {

            if (dnode->datatype == DICT_DTYPE_UINT8) {
                fprintf(stdout, "%u  ", (BITSET_MID(*((uint8_t *)data), bitfrom, bitto)));

            } else if (dnode->datatype == DICT_DTYPE_UINT16) {
                fprintf(stdout, "%u  ", (BITSET_MID(*((uint16_t *)data), bitfrom, bitto)));

            } else if (dnode->datatype == DICT_DTYPE_UINT32) {
                fprintf(stdout, "%u",   (BITSET_MID(*((uint32_t *)data), bitfrom, bitto)));

            } else if (dnode->datatype == DICT_DTYPE_UINT64) {
                fprintf(stdout, "%lu",  (BITSET_MID(*((uint64_t *)data), bitfrom, bitto)));
            }

            break;
        }
    }
    fprintf(stdout, "\n");

    return NULL;
}

pdu_node_t *
pdu_node_get_root(void *context)
{
    return &pdu_tree.nodes[0];
}

void
pdu_node_trace(pdu_node_t *node)
{

}
