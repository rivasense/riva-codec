#include <byteswap.h>
#include <stdio.h>

#include "../pdu.h"
#include "s1ap.h"
#include "s1ap_dict.h"
#include "s1ap_fields.h"

void
s1ap_decode_fields(char *data, uint16_t size, pdu_node_t *parent, uint8_t pcode)
{
    osi_s1ap_valhead_t *valhead = (void *)data;

    if (valhead->items > 0) {
        pdu_node_t *ie_items = pdu_node_mk("protocolIEs",
                parent, (char*)(valhead+1), size - sizeof(*valhead));
        data += sizeof(*valhead);
        for (uint8_t item = 0; item < valhead->items; item++) {

            osi_s1ap_valitem_head_t *valitem = (void *)data;
            //uint16_t critically   = bswap_16(valitem->critval) >> 14;
            uint16_t valsize      = bswap_16(valitem->critval) & 0xFFF;

            pdu_node_t *ie_item = pdu_node_mk("protocolIE-field",
                    ie_items, (char*)(valhead+1), size - sizeof(*valhead));
            pdu_node_mk("id", ie_item, (char*)&valitem->id, 0);
            pdu_node_mkbitset("critically", ie_item, (char *)&valitem->critval, 6, 8);
            pdu_node_mkbitset("valueSize",  ie_item, (char *)&valitem->critval, 8, 16);

            data += sizeof(*valitem);
            s1ap_decfield_func decode_func;

            ie_item = pdu_node_mk("value", ie_item, (char*)data, valsize);

            s1ap_fields_getfunc(&decode_func, pcode, bswap_16(valitem->id));

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
    pdu_dict_register(dict_nodes);

    pdu_node_t *root = pdu_node_mkpacket(data, size, NULL);
    pdu_node_t *S1AP = pdu_node_mk("S1AP", root, data, size);
    pdu_node_t *S1AP_PDU = pdu_node_mk("S1AP-PDU", S1AP, data, size);

    osi_s1ap_head_t *head = (void *)data;

    switch(head->pdu_code) {
    case 0: S1AP_PDU = pdu_node_mk("initiatingMessage",   S1AP_PDU, data, size);
            break;
    case 1: S1AP_PDU = pdu_node_mk("successfulOutcome",   S1AP_PDU, data, size);
            break;
    case 2: S1AP_PDU = pdu_node_mk("unsuccessfulOutcome", S1AP_PDU, data, size);
            break;
    }

    pdu_node_mkbitset("pduType",    S1AP_PDU, (char *)head, 5, 8);
    pdu_node_mk("procedureCode",    S1AP_PDU, (char *)&head->procedure_code, 0);
    pdu_node_mkbitset("critically", S1AP_PDU, (char *)&head->critval, 0, 4);
    pdu_node_mkbitset("valueSize",  S1AP_PDU, (char *)&head->critval, 8, 16);

    //uint16_t critically     = bswap_16(head->critval) >> 14;
    uint16_t valsize        = bswap_16(head->critval) & 0xFFF;

    pdu_node_t *S1AP_VALUE = pdu_node_mk("value", S1AP_PDU, (char*)(head + 1), valsize);
    char       *valname = NULL;

    switch (head->procedure_code) {
    case 10: valname = "Paging"; break;
    case 21: valname = "UEContextModificationRequest"; break;
    case 23: valname = "UEContextRelease"; break;
    }
    if (!valname) {
        return;
    }
    S1AP_VALUE = pdu_node_mk(valname, S1AP_VALUE, (char*)(head + 1), valsize);

    s1ap_decode_fields((char*)(head + 1), valsize, S1AP_VALUE, head->procedure_code);

    pdu_node_trace(root);
}
