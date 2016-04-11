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

int s1ap_fields_getfunc(s1ap_decfield_func *decode_func,
                        uint8_t             procedure_code,
                        uint16_t            protocol_id)
{
    switch(protocol_id) {
    case 0: *decode_func = pid_0_MME_UE_ID;
        break;
    case 8: *decode_func = pid_8_ENB_UE_ID;
        break;
    default: *decode_func = NULL;
    }
    return 0;
}
