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

    uint16_t ipadding;
    for (ipadding = 0; data[ipadding]; ipadding++);

    pdu_node_cursor(parent, ipadding + 2, PDU_CURSOFF_INC);

    uint8_t items  = *(uint8_t*)pdu_node_cursor(parent, 1, PDU_CURSOFF_INC);

    if (items > 0) {
        pdu_node_t *ie_items = pdu_node_mksize("protocolIEs",
                parent, size - parent->val.cursor);

        /* TODO: simplify */
        for (uint8_t item = 0; item < items; item++) {

            pdu_node_t *ie_item = pdu_node_mk("ProtocolIE-Field", ie_items);

            pdu_node_t *field;
            uint16_t    id, valsize;

            field = pdu_node_mknext("id", ie_item);
            pdu_node_get_value(field, &id);

            field = pdu_node_mk("criticality",  ie_item);
            field = pdu_node_mknext(".valsize", ie_item);
            pdu_node_get_value(field, &valsize);

            ie_item->val.size = valsize + 2 + 2;
            pdu_node_cursor(ie_items, valsize + 2 + 2, PDU_CURSOFF_INC);


            ie_item = pdu_node_mkdatasize("value", ie_item, ie_item->val.data + 2 + 2, valsize);

            s1ap_pie_func decode_func = s1ap_pies[id].func;
            if (decode_func) {
                decode_func(ie_item,
                            pdu_node_cursor(ie_item, 0, PDU_CURSOFF_NONE),
                            valsize);
            }
        }
    }
}

void
s1ap_decode(char *data, uint16_t size, void *context)
{
    pdu_fields_register(s1ap_fields);

    pdu_node_t *root = pdu_node_mkpacket(data, size, NULL);
    pdu_node_t *S1AP_PDU = pdu_node_mkdatasize("S1AP-PDU", root, data, size);

    uint8_t pdu_code = *(uint8_t *)pdu_node_cursor(S1AP_PDU, 0, PDU_CURSOFF_NONE);

    switch(pdu_code >> 5) {
    case 0: S1AP_PDU = pdu_node_mkdatasize("initiatingMessage",   S1AP_PDU, data, size);
            break;
    case 1: S1AP_PDU = pdu_node_mkdatasize("successfulOutcome",   S1AP_PDU, data, size);
            break;
    case 2: S1AP_PDU = pdu_node_mkdatasize("unsuccessfulOutcome", S1AP_PDU, data, size);
            break;
    }

    pdu_node_cursor(S1AP_PDU, sizeof(uint8_t), PDU_CURSOFF_INC);

    pdu_node_t *field;
    uint8_t     proccode;
    uint16_t    valsize;

    field = pdu_node_mknext("procedureCode", S1AP_PDU);
    pdu_node_get_value(field, &proccode);

    field = pdu_node_mk("criticality",  S1AP_PDU);
    field = pdu_node_mknext(".valsize", S1AP_PDU);
    pdu_node_get_value(field, &valsize);

    /* TODO: add proccode section as pdu node */

    S1AP_PDU = pdu_node_mksize("value", S1AP_PDU, size - S1AP_PDU->val.cursor);

    s1ap_decode_fields(S1AP_PDU->val.data, valsize, S1AP_PDU, proccode);

    pdu_node_trace(root);
}
