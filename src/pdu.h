#ifndef __PDU_H__
#define __PDU_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define DICT_NTYPE_PDU          0x00
#define DICT_NTYPE_PROTO        0x01
#define DICT_NTYPE_SECTION      0x02
#define DICT_NTYPE_FIELD        0x03
#define DICT_NTYPE_BITSET       0x04

#define DICT_DTYPE_UINT8        0x01
#define DICT_DTYPE_UINT16       0x02
#define DICT_DTYPE_UINT24       0x03
#define DICT_DTYPE_UINT32       0x04
#define DICT_DTYPE_UINT40       0x05
#define DICT_DTYPE_UINT48       0x06
#define DICT_DTYPE_UINT56       0x07
#define DICT_DTYPE_UINT64       0x08

#define DICT_DTYPE_HEX8         0x11
#define DICT_DTYPE_HEX16        0x12
#define DICT_DTYPE_HEX24        0x13
#define DICT_DTYPE_HEX32        0x14
#define DICT_DTYPE_HEX40        0x15
#define DICT_DTYPE_HEX48        0x16
#define DICT_DTYPE_HEX56        0x17
#define DICT_DTYPE_HEX64        0x18

#define DICT_DTYPE_BYTES        0x20
#define DICT_DTYPE_CHAR         0x30
#define DICT_DTYPE_BITSET       0x40

typedef struct pdu_node  pdu_node_t;
typedef struct dict_code dict_code_t;
typedef struct dict_node dict_node_t;

typedef void (*dict_decode_func)(pdu_node_t *node, FILE *output);

struct dict_code {
    uint64_t     code;
    char        *name;
};

struct dict_node {
    char             *name;
    char             *description;
    uint32_t          nodetype;
    uint32_t          datatype;
    bool              visibility;
    dict_code_t      *codes;
    dict_decode_func  decode_func;
};

void
pdu_dict_register(dict_node_t *nodes);

struct pdu_node {
    char        *name;
    char        *description;
    bool         visibility;
    uint32_t     type;          // (proto, section, field, subfield)
    pdu_node_t  *next;          // next node at same level
    pdu_node_t  *child_f;       // first child
    pdu_node_t  *child_l;       // last  child
    struct pdu_node_value {
        uint32_t     type;      // (uint8/uint16/uint32/uint64/ .... hex(...) ... byte ... char ... bitset)
        char        *data;      // data begin pointer
        uint16_t     size;      // data size in bytes
        uint16_t     bitfrom;   //
        uint16_t     bitto;     //
        void        *encoder;   // encoder method
        void        *decoder;   // decoder method
    } val;
};

pdu_node_t *
pdu_node_mkpacket(char *data, uint16_t size, void *context);

pdu_node_t *
pdu_node_mk      (char *name, pdu_node_t *parent, char *data, uint16_t size);

pdu_node_t *
pdu_node_mkbitset(char *name, pdu_node_t *parent, char *data, uint16_t bitfrom, uint16_t bitto);

pdu_node_t *
pdu_node_get_root(void *context);

void
pdu_node_trace(pdu_node_t *node);

#endif
