#include <byteswap.h>

#include "s1ap.h"
#include "s1ap_fields.h"

static void
pid_0_MME_UE_ID(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_mk("MME-UE-s1AP-ID", node, (char*)data, 0);
}

static void
pid_8_ENB_UE_ID(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_mk("ENB-UE-s1AP-ID", node, (char*)data, 0);
}

static void
pid_43_UEPagingID(pdu_node_t *node, char *data, uint16_t size)
{
    node = pdu_node_mk("UEPagingID", node, data, size);
    node = pdu_node_mk("s-TMSI",     node, data, size);

    struct s1ap_43_UEPagingID *field = (void *)data;
    pdu_node_mk("mMEC",   node, (char*)&field->mmec, 0);
    pdu_node_mk("m-TMSI", node, (char*)&field->mtmsi, 0);
}

static void
pid_46_TAIList(pdu_node_t *node, char *data, uint16_t size)
{
    uint8_t *items = (void *)data;
    node = pdu_node_mk("TAIList", node, data, size);
    data++; size--;

    for (uint8_t item = 0; item <= *items; item++) {

        osi_s1ap_valitem_head_t *valitem = (void *)data;
        uint16_t valsize                 = bswap_16(valitem->critval) & 0xFFF;

        pdu_node_t *ie_item = pdu_node_mk("protocolIE-SingleContainer",
                node, data, size - sizeof(*valitem) - valsize);
        pdu_node_mk("id", ie_item, (char*)&valitem->id, 0);
        pdu_node_mkbitset("critically", ie_item, (char *)&valitem->critval, 6, 8);
        pdu_node_mkbitset("valueSize",  ie_item, (char *)&valitem->critval, 8, 16);

        data += sizeof(*valitem);
        s1ap_decfield_func decode_func;

        ie_item = pdu_node_mk("value", ie_item, (char*)data, valsize);

        s1ap_fields_getfunc(&decode_func, 0, bswap_16(valitem->id));

        if (decode_func) {
            decode_func(ie_item, (char*)data, valsize);
        }

        data += valsize;
    }
}

static void
pid_47_TAIItem(pdu_node_t *node, char *data, uint16_t size)
{
    node = pdu_node_mk("TAIItem", node, data, size);

    struct s1ap_46_TAIItem *titem = (void *)data;
    pdu_node_mk("pLMNIdentity", node, (char *)&titem->PLMNId, 0);
    pdu_node_mk("tAC",          node, (char *)&titem->tAC, 0);
    // TODO: MCC, MNC here
}


static void
pid_80_UEIdentityIndexValue(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_mk("UEIdentityIndexValue", node, (char*)data, 0);
}

static void
pid_109_CNDomain(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_mk("CNDomain", node, (char*)data, 0);
}

int s1ap_fields_getfunc(s1ap_decfield_func *decode_func,
                        uint8_t             procedure_code,
                        uint16_t            protocol_id)
{
    switch(protocol_id) {
    case 0: *decode_func = pid_0_MME_UE_ID;
        break;
    case 8: *decode_func = pid_8_ENB_UE_ID;
        break;
    case 43: *decode_func = pid_43_UEPagingID;
        break;
    case 46: *decode_func = pid_46_TAIList;
        break;
    case 47: *decode_func = pid_47_TAIItem;
        break;
    case 80: *decode_func = pid_80_UEIdentityIndexValue;
        break;
    case 109: *decode_func = pid_109_CNDomain;
        break;

    default: *decode_func = NULL;
    }
    return 0;
}
