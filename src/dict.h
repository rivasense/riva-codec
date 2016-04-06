#ifndef __DICT_H__
#define __DICT_H__

#include <stdbool.h>
#include <stdint.h>
#if 0
#define DICT_FIELD_TYPE_UINT8        0x01
#define DICT_FIELD_TYPE_UINT16       0x02
#define DICT_FIELD_TYPE_UINT24       0x03
#define DICT_FIELD_TYPE_UINT32       0x04
#define DICT_FIELD_TYPE_UINT40       0x05
#define DICT_FIELD_TYPE_UINT48       0x06
#define DICT_FIELD_TYPE_UINT56       0x07
#define DICT_FIELD_TYPE_UINT64       0x08

#define DICT_FIELD_TYPE_HEX8         0x11
#define DICT_FIELD_TYPE_HEX16        0x12
#define DICT_FIELD_TYPE_HEXT24       0x13
#define DICT_FIELD_TYPE_HEXT32       0x14
#define DICT_FIELD_TYPE_HEXT40       0x15
#define DICT_FIELD_TYPE_HEXT48       0x16
#define DICT_FIELD_TYPE_HEXT56       0x17
#define DICT_FIELD_TYPE_HEXT64       0x18

#define DICT_FIELD_TYPE_BYTES        0x20
#define DICT_FIELD_TYPE_CHAR         0x30
#define DICT_FIELD_TYPE_BITSET       0x40

typedef struct dict_code {
    uint64_t     code;
    char        *name;
} dict_code_t;

typedef struct dict_proto {
    uint32_t     id;
    char        *name;
    char        *description;
} dict_proto_t;

typedef struct dict_sect {
    uint32_t     id;
    char        *name;
    char        *description;
    bool         visibility;
} dict_sect_t;

typedef struct dict_field {
    uint32_t     id;
    char        *name;
    char        *description;
    uint32_t     type;
    bool         visibility;
    dict_code_t *codes;
} dict_field_t;
#endif

#define DICT_NTYPE_PDU          0x00
#define DICT_NTYPE_PROTO        0x01
#define DICT_NTYPE_SECTION      0x02
#define DICT_NTYPE_FIELD        0x03
#define DICT_NTYPE_SUBFIELD     0x04

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
#define DICT_DTYPE_HEXT24       0x13
#define DICT_DTYPE_HEXT32       0x14
#define DICT_DTYPE_HEXT40       0x15
#define DICT_DTYPE_HEXT48       0x16
#define DICT_DTYPE_HEXT56       0x17
#define DICT_DTYPE_HEXT64       0x18

#define DICT_DTYPE_BYTES        0x20
#define DICT_DTYPE_CHAR         0x30
#define DICT_DTYPE_BITSET       0x40

typedef struct dict_code dict_code_t;
typedef struct dict_node dict_node_t;

typedef void (*dict_decode_func)(void *node);

struct dict_code {
    uint64_t     code;
    char        *name;
};

struct dict_node {
    char        *name;
    char        *description;
    uint32_t     nodetype;
    uint32_t     datatype;
    bool         visibility;
    dict_code_t *codes;
};

#endif
