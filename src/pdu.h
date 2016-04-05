#ifndef __PDU_H__
#define __PDU_H__

#include <stdbool.h>
#include <stdint.h>

#include "dict.h"

void
pdu_dict_register(dict_proto_t *protos, dict_sect_t *sects, dict_field_t *fields);

typedef struct pdu_node pdu_node_t;
struct pdu_node {
    uint32_t     id;
    char        *name;
    char        *description;
    bool         visibility;
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
pdu_node_get_root(void *context);

void
pdu_node_trace(pdu_node_t *node);

#endif
