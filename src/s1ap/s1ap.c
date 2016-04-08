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

        {"pduType",             "",                        DICT_NTYPE_BITSET,  DICT_DTYPE_UINT8, false,NULL, NULL},
        {"procedureCode",       "",                        DICT_NTYPE_FIELD,   DICT_DTYPE_UINT8, true, NULL, NULL},
        {"critically",          "",                        DICT_NTYPE_BITSET,  DICT_DTYPE_UINT16,true, NULL, NULL},
        {"valueSize",           "",                        DICT_NTYPE_BITSET,  DICT_DTYPE_UINT16,true, NULL, NULL},

        /* ---- */
        {"UEContextReleaseComplete",  "",                  DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"protocolIEs",               "",                  DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"protocolIE-field",          "",                  DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

        {"id",                     "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT16,true, NULL, NULL},
        {"MME-UE-s1AP-ID",         "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT24,true, NULL, NULL},
        {"ENB-UE-s1AP-ID",         "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT16,true, NULL, NULL},

        {NULL,                  NULL,                      0,                  0,                true, NULL, NULL}
};

static void
decode_pc_ContextRelease(char *data, uint16_t size, pdu_node_t *parent)
{
    pdu_node_t *rc = pdu_node_mk(".UEContextReleaseComplete", parent, data, size);

    osi_s1ap_valhead_t *valhead = (void *)data;

    if (valhead->items > 0) {
        pdu_node_t *ie_items = pdu_node_mk(".protocolIEs",
                rc, (char*)(valhead+1), size - sizeof(*valhead));
        data += sizeof(*valhead);
        for (uint8_t item = 0; item < valhead->items; item++) {
            osi_s1ap_valitem_head_t *valitem = (void *)data;

            pdu_node_t *ie_item = pdu_node_mk(".protocolIE-field",
                    ie_items, (char*)(valhead+1), size - sizeof(*valhead));
            pdu_node_mk(".id", ie_item, (char*)&valitem->id, 0);
            pdu_node_mkbitset(".critically", ie_item, (char *)&valitem->critval, 6, 8);
            pdu_node_mkbitset(".valueSize",  ie_item, (char *)&valitem->critval, 8, 16);

            data += sizeof(*valitem);
            switch(bswap_16(valitem->id)) {
            case 0: pdu_node_mk(".MME-UE-s1AP-ID", ie_item, (char*)data, 0);
                break;
            case 8: pdu_node_mk(".ENB-UE-s1AP-ID", ie_item, (char*)data, 0);
                break;
            }

            //uint16_t critically   = bswap_16(valitem->critval) >> 14;
            //uint16_t valsize      = bswap_16(valitem->critval) & 0xFFF;
            data += bswap_16(valitem->critval) & 0xFFF;
        }
    }
}

void s1ap_decode(char *data, uint16_t size, void *context)
{
    pdu_dict_register(dict_nodes);

    pdu_node_t *root = pdu_node_mkpacket(data, size, NULL);
    pdu_node_t *S1AP = pdu_node_mk(".S1AP", root, data, size);
    pdu_node_t *S1AP_PDU = pdu_node_mk(".S1AP-PDU", S1AP, data, size);

    osi_s1ap_head_t *head = (void *)data;
    pdu_node_t      *s1ap = NULL;

    switch(head->pdu_code) {
    case 0: s1ap = pdu_node_mk(".initiatingMessage",   S1AP_PDU, data, size);
            break;
    case 1: s1ap = pdu_node_mk(".successfulOutcome",   S1AP_PDU, data, size);
            break;
    case 2: s1ap = pdu_node_mk(".unsuccessfulOutcome", S1AP_PDU, data, size);
            break;
    }

    pdu_node_mkbitset(".pduType", s1ap, (char *)head, 5, 8);
    pdu_node_mk(".procedureCode", s1ap, (char *)&head->procedure_code, 0);
    pdu_node_mkbitset(".critically", s1ap, (char *)&head->critval, 0, 4);
    pdu_node_mkbitset(".valueSize",  s1ap, (char *)&head->critval, 8, 16);

    uint16_t critically   = bswap_16(head->critval) >> 14;
    uint16_t valsize      = bswap_16(head->critval) & 0xFFF;

    switch (head->procedure_code) {
    case 23: decode_pc_ContextRelease((char*)(head + 1), valsize, s1ap);
    }

    fprintf(stdout,
            "\t PDU code: %u, procedure code: %u, critically: %u, valsize: %u\n",
            head->pdu_code, head->procedure_code, critically, valsize);
    fprintf(stdout, "\n");

    pdu_node_trace(root);
}
