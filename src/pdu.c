#include <string.h>
#include "pdu.h"

typedef struct pdu_tree {
    pdu_node_t nodes[0xFFFF];
    uint32_t   cursor;
} pdu_tree_t;

static pdu_tree_t pdu_tree;

void
pdu_dict_register(dict_proto_t *protos, dict_sect_t *sects, dict_field_t *fields)
{

}

pdu_node_t *
pdu_node_get_child(pdu_node_t *node)
{
    node->child = &pdu_tree.nodes[pdu_tree.cursor++];
    return node->child;
}

pdu_node_t *
pdu_node_get_next(pdu_node_t *node)
{
    node->next = &pdu_tree.nodes[pdu_tree.cursor++];
    return node->next;
}

pdu_node_t *
pdu_tree_clean(void *context)
{
    memset(pdu_tree.nodes, 0, sizeof(pdu_tree.nodes[0]) * pdu_tree.cursor);
    pdu_tree.cursor = 0;
    return &pdu_tree.nodes[pdu_tree.cursor];
}

pdu_node_t *
pdu_node_mkpacket(char *data, uint16_t size, void *context)
{
    return NULL;
}

pdu_node_t *
pdu_node_mkproto_child(pdu_node_t *node, uint32_t id, char *data, uint16_t size)
{
    return NULL;
}

pdu_node_t *
pdu_node_mksect_child(pdu_node_t *node, uint32_t id, char *data, uint16_t size)
{
    return NULL;
}

pdu_node_t *
pdu_node_mkfield_child(pdu_node_t *node, uint32_t id, char *data, uint16_t size)
{
    return NULL;
}

pdu_node_t *
pdu_node_mksubfield_child(pdu_node_t *node, uint32_t id, uint16_t bitoff, uint16_t bitsize)
{
    return NULL;
}

pdu_node_t *
pdu_node_mk_sibling(pdu_node_t *node, uint32_t id,
                    char *data, uint16_t size, uint16_t bitoff, uint16_t bitsize)
{
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
