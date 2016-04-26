#ifndef __S1AP_FIELDS_H__
#define __S1AP_FIELDS_H__

#include <stdint.h>
#include "../pdu.h"

typedef void (*s1ap_decfield_func)(pdu_node_t *node, char *data, uint16_t size);

int s1ap_fields_getfunc(s1ap_decfield_func *decode_func,
                        uint8_t             procedure_code,
                        uint16_t            protocol_id);

#pragma pack(push, 1)

struct s1ap_43_UEPagingID {
    uint8_t mmec;
    uint8_t mmec_;
    uint32_t mtmsi;
};

struct s1ap_47_TAIItem {
    uint8_t  padding;
    uint8_t  PLMNId[3];
    uint16_t tAC;
};

struct s1ap_66_UEAggregateMaximumBitrate {
    uint8_t   padding0;
    uint32_t  uEaggregateMaximumBitRateDL;
    uint8_t   padding1;
    uint32_t  uEaggregateMaximumBitRateUL;
};

struct s1ap_67_TAI {
    uint8_t  padding;
    uint8_t  PLMNId[3];
    uint16_t tAC;
};

struct s1ap_99_UE_S1AP_IDs {
    uint8_t   padding0;
    uint32_t  mMe;
    uint8_t   padding1;
    uint16_t  eNB;
};

struct s1ap_100_EUTRAN_CGI {
    uint8_t  padding;
    uint8_t  PLMNId[3];
    uint32_t cellID;
};

#pragma pack(pop)

#endif
