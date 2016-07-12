#include <byteswap.h>
#include <stdint.h>
#include <stdio.h>

#include "../pdu.h"
#include "s1ap.h"
#include "s1ap_dict.h"
#include "s1ap_proto_ies.h"


void
s1ap_decode_container(char *name, pdu_node_t *node, char *data, uint16_t size)
{
    uint8_t *items = (void *)data;
    node = pdu_node_mkdatasize("TAIList", node, data, size);
    data++; size--;

    for (uint8_t item = 0; item <= *items; item++) {

        osi_s1ap_valitem_head_t *valitem = (void *)data;
        uint16_t valsize                 = bswap_16(valitem->critval) & 0xFFF;

        pdu_node_t *ie_item = pdu_node_mkdatasize(name,
                node, data, size - sizeof(*valitem) - valsize);
        pdu_node_mkdatasize("id", ie_item, (char*)&valitem->id, 0);
        pdu_node_mkdatasize("critically", ie_item, (char *)&valitem->critval, 6, 8);
        pdu_node_mkdatasize("valueSize",  ie_item, (char *)&valitem->critval, 8, 16);

        data += sizeof(*valitem);
        s1ap_pie_func decode_func = s1ap_pies[bswap_16(valitem->id)].func;

        ie_item = pdu_node_mkdatasize("value", ie_item, (char*)data, valsize);

        if (decode_func) {
            decode_func(ie_item, (char*)data, valsize);
        }

        data += valsize;
    }
}

void
s1ap_decode_fields(char *data, uint16_t size, pdu_node_t *parent, uint8_t pcode)
{
    for (; *data; data++);
    osi_s1ap_valhead_t *valhead = (void *)data;

    if (valhead->items > 0) {
        pdu_node_t *ie_items = pdu_node_mkdatasize("protocolIEs",
                parent, (char*)(valhead+1), size - sizeof(*valhead));
        data += sizeof(*valhead);
        for (uint8_t item = 0; item < valhead->items; item++) {

            osi_s1ap_valitem_head_t *valitem = (void *)data;
            //uint16_t critically   = bswap_16(valitem->critval) >> 14;
            uint16_t valsize      = bswap_16(valitem->critval) & 0xFFF;

            pdu_node_t *ie_item = pdu_node_mkdatasize("protocolIE-field",
                    ie_items, (char*)(valhead+1), size - sizeof(*valhead));
            pdu_node_mkdatasize("id", ie_item, (char*)&valitem->id, 0);
            pdu_node_mkdatasize("critically", ie_item, (char *)&valitem->critval, 6, 8);
            pdu_node_mkdatasize("valueSize",  ie_item, (char *)&valitem->critval, 8, 16);

            data += sizeof(*valitem);
            s1ap_pie_func decode_func = s1ap_pies[bswap_16(valitem->id)].func;

            ie_item = pdu_node_mkdatasize("value", ie_item, (char*)data, valsize);

            if (decode_func) {
                decode_func(ie_item, (char*)data, valsize);
            }

            data += valsize;
        }
    }
}

void
s1ap_decode(char *data, uint16_t size, void *context)
{
    pdu_fields_register(s1ap_fields);

    pdu_node_t *root = pdu_node_mkpacket(data, size, NULL);
    pdu_node_t *S1AP_PDU = pdu_node_mkdatasize("S1AP-PDU", root, data, size);
    osi_s1ap_head_t *head = (void *)data;

    switch(head->pdu_code) {
    case 0: S1AP_PDU = pdu_node_mkdatasize("initiatingMessage",   S1AP_PDU, data, size);
            break;
    case 1: S1AP_PDU = pdu_node_mkdatasize("successfulOutcome",   S1AP_PDU, data, size);
            break;
    case 2: S1AP_PDU = pdu_node_mkdatasize("unsuccessfulOutcome", S1AP_PDU, data, size);
            break;
    }

    //pdu_node_mk("pduType",       S1AP_PDU, (char *)head, 5, 8);
    //pdu_node_mkdatasize("procedureCode", S1AP_PDU, (char *)&head->procedure_code, 0);
    //pdu_node_mkdatasize("criticality",   S1AP_PDU, (char *)&head->critval, 0, 4);
    //pdu_node_mk("valueSize",     S1AP_PDU, (char *)&head->critval, 8, 16);

    //pdu_node_cursor(S1AP_PDU, sizeof(uint8_t), PDU_CURSOR_CUR);
    //pdu_node_mknext("procedureCode", S1AP_PDU);
    //pdu_node_mknext("criticality",   S1AP_PDU);

#if 0
    //uint16_t critically     = bswap_16(head->critval) >> 14;
    uint16_t valsize        = bswap_16(head->critval) & 0xFFF;

    pdu_node_t *S1AP_VALUE = pdu_node_mk("value", S1AP_PDU, (char*)(head + 1), valsize);
    char       *valname = NULL;

    if (head->procedure_code < s1ap_proccodes_sz) {
        valname = s1ap_proccodes[head->procedure_code].name;
    } else {
        return;
    }

    S1AP_VALUE = pdu_node_mk(valname, S1AP_VALUE, (char*)(head + 1), valsize);

    s1ap_decode_fields((char*)(head + 1), valsize, S1AP_VALUE, head->procedure_code);
#endif
    pdu_node_trace(root);
}
