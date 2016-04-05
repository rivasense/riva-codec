#include <byteswap.h>
#include <stdio.h>

#include "../dict.h"
#include "../pdu.h"
#include "s1ap.h"

#define P_S1AP      0x10000

static dict_proto_t
dict_protos[] = {
    {P_S1AP, "S1AP", "S1 Application Protocol"},
    {0,      NULL,   NULL}
};

enum dict_sect_e {
    S_S1AP_PDU = P_S1AP,
    S_initiatingMessage,
    S_successfulOutcome,
    S_unsuccessfulOutcome
};
static dict_sect_t
dict_sections[] = {
    {S_S1AP_PDU, "S1AP-PDU", NULL, false},
    {0,          NULL,       NULL, false}
};

enum dict_field_e {
    F_S1AP_PDU_TYPE = P_S1AP,
    F_procedureCode,
    F_critically,
    F_valsize,
};
static dict_field_t
dict_fields[] = {
    {F_S1AP_PDU_TYPE, NULL,            NULL, DICT_FIELD_TYPE_UINT8,  true, NULL},
    {F_procedureCode, "procedureCode", NULL, DICT_FIELD_TYPE_UINT8,  true, NULL},
    {F_critically,    "critically",    NULL, DICT_FIELD_TYPE_UINT16, true, NULL},
    {F_valsize,       "valueSize",     NULL, DICT_FIELD_TYPE_UINT16, true, NULL},

    {0,               NULL,            NULL, 0,                      false, NULL}
};

void s1ap_decode(char *data, uint16_t size, void *context)
{
    pdu_dict_register(dict_protos, dict_sections, dict_fields);

    pdu_node_t *root = pdu_node_mkpacket(data, size, NULL);
    pdu_node_t *s1ap = pdu_node_mkproto_child(root, P_S1AP, data, size);
    pdu_node_t *pdu  = pdu_node_mksect_child(s1ap, S_S1AP_PDU, data, size);

    osi_s1ap_head_t *head = (void *)data;
    uint16_t critically   = bswap_16(head->critval) >> 14;
    uint16_t valsize      = bswap_16(head->critval) & 0xFFF;

    pdu_node_t *status = NULL;

    switch(head->pdu_code) {
    case 0: status = pdu_node_mksect_child(pdu, S_initiatingMessage, data, size);
            break;
    case 1: status = pdu_node_mksect_child(pdu, S_successfulOutcome, data, size);
            break;
    case 2: status = pdu_node_mksect_child(pdu, S_unsuccessfulOutcome, data, size);
            break;
    }
    pdu_node_mksubfield_child(status, F_S1AP_PDU_TYPE, 0, 3);
    pdu_node_mkfield_child   (status, F_procedureCode, (char *)&head->procedure_code, 0);
    pdu_node_mksubfield_child(status, F_critically, 16,  2);
    pdu_node_mksubfield_child(status, F_valsize,    16 + 2, 14);

    fprintf(stdout,
            "\t PDU code: %u, procedure code: %u, critically: %u, valsize: %u\n",
            head->pdu_code, head->procedure_code, critically, valsize);
}
