#ifndef __S1AP_FIELDS_H__
#define __S1AP_FIELDS_H__

#include <stdint.h>
#include "../pdu.h"

typedef void (*s1ap_decfield_func)(pdu_node_t *node, char *data, uint16_t size);

int s1ap_fields_getfunc(s1ap_decfield_func *decode_func,
                        uint8_t             procedure_code,
                        uint16_t            protocol_id);

#endif
