#include <byteswap.h>
#include <stdio.h>

#include "../pdu.h"
#include "s1ap.h"

#define P_S1AP      0x10000

static struct dict_node
dict_nodes[] = {
        {"S1AP",                "S1 Application Protocol", DICT_NTYPE_PROTO,   DICT_DTYPE_BYTES, true, NULL, NULL},
        {"S1AP-PDU",            "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"initiatingMessage",   "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"successfulOutcome",   "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"unsuccessfulOutcome", "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

        {"pduType",             "",                        DICT_NTYPE_BITSET,  DICT_DTYPE_UINT8,  false,NULL, NULL},
        {"procedureCode",       "",                        DICT_NTYPE_FIELD,   DICT_DTYPE_UINT8,  true, NULL, NULL},
        {"critically",          "",                        DICT_NTYPE_BITSET,  DICT_DTYPE_UINT16, true, NULL, NULL},
        {"valueSize",           "",                        DICT_NTYPE_BITSET,  DICT_DTYPE_UINT16, true, NULL, NULL},

        {NULL,                  NULL,                      0,                0,                   true, NULL, NULL}
};

void s1ap_decode(char *data, uint16_t size, void *context)
{
    pdu_dict_register(dict_nodes);

    pdu_node_mkpacket(data, size, NULL);
    pdu_node_mk("S1AP", NULL, data, size);
    pdu_node_mk("S1AP.S1AP-PDU", NULL, data, size);

    osi_s1ap_head_t *head = (void *)data;
    pdu_node_t      *s1ap = NULL;

    switch(head->pdu_code) {
    case 0: s1ap = pdu_node_mk("S1AP.S1AP-PDU.initiatingMessage",   NULL, data, size);
            break;
    case 1: s1ap = pdu_node_mk("S1AP.S1AP-PDU.successfulOutcome",   NULL, data, size);
            break;
    case 2: s1ap = pdu_node_mk("S1AP.S1AP-PDU.unsuccessfulOutcome", NULL, data, size);
            break;
    }

    pdu_node_mkbitset(".pduType", s1ap, (char *)head, 5, 8);
    pdu_node_mk(".procedureCode", s1ap, (char *)&head->procedure_code, 0);
    pdu_node_mkbitset(".critically", s1ap, (char *)&head->critval, 0, 4);
    pdu_node_mkbitset(".valueSize",  s1ap, (char *)&head->critval, 8, 16);

    uint16_t critically   = bswap_16(head->critval) >> 14;
    uint16_t valsize      = bswap_16(head->critval) & 0xFFF;
    fprintf(stdout,
            "\t PDU code: %u, procedure code: %u, critically: %u, valsize: %u\n",
            head->pdu_code, head->procedure_code, critically, valsize);
}
