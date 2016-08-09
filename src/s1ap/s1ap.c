#include <byteswap.h>
#include <stdint.h>
#include <stdio.h>

#include "../pdu.h"
#include "s1ap.h"
#include "s1ap_dict.h"
#include "s1ap_proto_ies.h"

void
s1ap_decode_ie(pdu_node_t *parent, uint16_t ie, char *data, uint16_t size)
{
    s1ap_pie_func decode_func = s1ap_pies[ie].func;
    if (decode_func) {
        decode_func(parent, data, size);
    }
}

void
s1ap_decode_list(pdu_node_t *parent, char *lname, char *iname, char *data, uint16_t size)
{
    pdu_node_t *ie_items = pdu_node_mksize(lname, parent, size);
    pdu_node_cursor(ie_items, 1, PDU_CURSOFF_INC);

    for (;;) {
        pdu_node_t *ie_item = pdu_node_mk(iname, ie_items);

        pdu_node_t *field;
        uint16_t    id, valsize;

        field = pdu_node_mknext("id", ie_item);
        pdu_node_get_value(field, &id);

        field = pdu_node_mk("criticality", ie_item);
        field = pdu_node_mknext("valsize", ie_item);
        pdu_node_get_value(field, &valsize);

        pdu_node_cursor(ie_items, valsize + 2 + 2, PDU_CURSOFF_INC);
        ie_item->val.size = valsize + 2 + 2;
        ie_item = pdu_node_mkdatasize("value", ie_item, ie_item->val.data + 2 + 2, valsize);

        s1ap_decode_ie(ie_item, id, pdu_node_cursor(ie_item, 0, PDU_CURSOFF_NONE), valsize);

        if (ie_items->val.cursor + 2 + 2 >= size) {
            break;
        }
    }
}

void
s1ap_decode_container(pdu_node_t *parent, uint8_t pcode, char *data, uint16_t size)
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

            field = pdu_node_mk("criticality", ie_item);
            field = pdu_node_mknext("valsize", ie_item);
            pdu_node_get_value(field, &valsize);

            ie_item->val.size = valsize + 2 + 2;
            pdu_node_cursor(ie_items, valsize + 2 + 2, PDU_CURSOFF_INC);


            ie_item = pdu_node_mkdatasize("value", ie_item, ie_item->val.data + 2 + 2, valsize);

            s1ap_decode_ie(ie_item, id, pdu_node_cursor(ie_item, 0, PDU_CURSOFF_NONE), valsize);
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

    field = pdu_node_mk("criticality", S1AP_PDU);
    field = pdu_node_mknext("valsize", S1AP_PDU);
    pdu_node_get_value(field, &valsize);

    /* TODO: add proccode section as pdu node */

    S1AP_PDU = pdu_node_mksize("value", S1AP_PDU, size - S1AP_PDU->val.cursor);

    s1ap_decode_container(S1AP_PDU, proccode, S1AP_PDU->val.data, valsize);

    pdu_node_trace(root);
}
