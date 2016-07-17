#ifndef __S1AP_H__
#define __S1AP_H__

#include <stdint.h>
#include "../pdu.h"

#pragma pack(push, 1)

typedef struct osi_s1ap_head_s
{
    uint8_t  pdu_code_padding:5;
    uint8_t  pdu_code        :3;
    uint8_t  procedure_code;
    uint16_t critval;
} osi_s1ap_head_t;

typedef struct osi_s1ap_valhead_s
{
    uint16_t  padding;
    uint8_t   items;
} osi_s1ap_valhead_t;

typedef struct osi_s1ap_valitem_head_s
{
    uint16_t id;
    uint16_t critval;
} osi_s1ap_valitem_head_t;

#pragma pack(pop)

void s1ap_decode_list(pdu_node_t *parent, char *lname, char *iname, char *data, uint16_t size);

void s1ap_decode_container(pdu_node_t *parent, uint8_t pcode, char *data, uint16_t size);

void s1ap_decode_ie(pdu_node_t *parent, uint16_t ie, char *data, uint16_t size);

void s1ap_decode(char *data, uint16_t size, void *context);

#endif
