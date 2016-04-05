#ifndef __PDU_H__
#define __PDU_H__

#include <stdint.h>

/* pdu_node_t::type         */
#define PDU_NODE_TYPE_PACKET        0
#define PDU_NODE_TYPE_PROTO         1
#define PDU_NODE_TYPE_SECTION       2
#define PDU_NODE_TYPE_FIELD         3
#define PDU_NODE_TYPE_SUBFIELD      4

/* pdu_node_t::data::type   */
#define PDU_NODE_DTYPE_UINT8        0x01
#define PDU_NODE_DTYPE_UINT16       0x02
#define PDU_NODE_DTYPE_UINT24       0x03
#define PDU_NODE_DTYPE_UINT32       0x04
#define PDU_NODE_DTYPE_UINT40       0x05
#define PDU_NODE_DTYPE_UINT48       0x06
#define PDU_NODE_DTYPE_UINT56       0x07
#define PDU_NODE_DTYPE_UINT64       0x08

#define PDU_NODE_DTYPE_HEX8         0x11
#define PDU_NODE_DTYPE_HEX16        0x12
#define PDU_NODE_DTYPE_HEXT24       0x13
#define PDU_NODE_DTYPE_HEXT32       0x14
#define PDU_NODE_DTYPE_HEXT40       0x15
#define PDU_NODE_DTYPE_HEXT48       0x16
#define PDU_NODE_DTYPE_HEXT56       0x17
#define PDU_NODE_DTYPE_HEXT64       0x18

#define PDU_NODE_DTYPE_BYTES        0x20
#define PDU_NODE_DTYPE_CHAR         0x30
#define PDU_NODE_DTYPE_BITSET       0x40

typedef struct pdu_node pdu_node_t;
struct pdu_node {
    uint32_t     id;
    char        *name;
    char        *description;
    uint32_t     type;          // (proto, section, field, subfield)
    pdu_node_t  *next;          // next node at same level
    pdu_node_t  *child;         // first child
    struct pdu_node_value {
        uint32_t     type;      // (uint8/uint16/uint32/uint64/ .... hex(...) ... byte ... char ... bitset)
        char        *data;      // data begin pointer
        uint16_t     size;      // data size in bytes
        uint16_t     bitoff;    // bit offset, for subfields only
        uint16_t     bitsize;   // bit size, for subfields only
        void        *encoder;   // encoder method
        void        *decoder;   // decoder method
    } value;
};

pdu_node_t *
pdu_node_mkpacket(char *data, uint16_t size, void *context);

pdu_node_t *
pdu_node_mkproto_child(pdu_node_t *node, uint32_t id, char *data, uint16_t size);

pdu_node_t *
pdu_node_mksect_child(pdu_node_t *node, uint32_t id, char *data, uint16_t size);

pdu_node_t *
pdu_node_mkfield_child(pdu_node_t *node, uint32_t id, char *data, uint16_t size);

pdu_node_t *
pdu_node_mksubfield_child(pdu_node_t *node, uint32_t id, uint16_t bitoff, uint16_t bitsize);

pdu_node_t *
pdu_node_mk_sibling(pdu_node_t *node, uint32_t id,
                    char *data, uint16_t size, uint16_t bitoff, uint16_t bitsize);

pdu_node_t *
pdu_tree_get_root(void *context);

void
pdu_tree_trace(pdu_node_t *node);

#endif
