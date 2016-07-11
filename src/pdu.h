#ifndef __PDU_H__
#define __PDU_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/*
 * PDU FIELD TYPES
 */
#define PDU_FT_UINT8        0x01
#define PDU_FT_UINT16       0x02
#define PDU_FT_UINT24       0x03
#define PDU_FT_UINT32       0x04
#define PDU_FT_UINT40       0x05
#define PDU_FT_UINT48       0x06
#define PDU_FT_UINT56       0x07
#define PDU_FT_UINT64       0x08

#define PDU_FT_HEX8         0x11
#define PDU_FT_HEX16        0x12
#define PDU_FT_HEX24        0x13
#define PDU_FT_HEX32        0x14
#define PDU_FT_HEX40        0x15
#define PDU_FT_HEX48        0x16
#define PDU_FT_HEX56        0x17
#define PDU_FT_HEX64        0x18

#define PDU_FT_BYTES        0x20
#define PDU_FT_CHAR         0x30
#define PDU_FT_BITSET       0x40

/*
 * PDU FIELD FLAGS
 */
#define PDU_FF_FIELD        0x00
#define PDU_FF_BITSET       0x01
#define PDU_FF_SECTION      0x02
#define PDU_FF_PROTO        0x03
#define PDU_FF_PDU          0x04


/*
 * PDU NODE CURSOR POSITION
 */
#define PDU_CURSOR_SET      0x00
#define PDU_CURSOR_CUR      0x01
#define PDU_CURSOR_END      0x02

/*
 *
 */
typedef struct pdu_field  pdu_field_t;
struct pdu_field {
    char       *name;
    uint32_t    type;
    uint64_t    mask;
    uint64_t    flags;
};

typedef struct pdu_node  pdu_node_t;
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
    } val;
};

void
pdu_fields_register (pdu_field_t *fields);

pdu_node_t *
pdu_node_get_root   (void *context);

void
pdu_node_trace      (pdu_node_t *node);

pdu_node_t *
pdu_node_mkpacket   (char *data, uint16_t size, void *context);

char *
pdu_node_cursor     (pdu_node_t *parent, int offset, int position);



pdu_node_t *
pdu_node_mk         (char *name, pdu_node_t *parent, ... );

pdu_node_t *
pdu_node_mknext     (char *name, pdu_node_t *parent, ... );

pdu_node_t *
pdu_node_mkdata     (char *name, pdu_node_t *parent, char *data, ... );

pdu_node_t *
pdu_node_mksize     (char *name, pdu_node_t *parent, size_t *size, ... );

pdu_node_t *
pdu_node_mkdatasize (char *name, pdu_node_t *parent, char *data, size_t size, ... );



#endif
