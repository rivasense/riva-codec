#ifndef __S1AP_DICT_H__
#define __S1AP_DICT_H__

#include "../pdu.h"

static struct dict_node
dict_nodes[] = {
        {"S1AP",                "S1 Application Protocol", DICT_NTYPE_PROTO,   DICT_DTYPE_BYTES, true, NULL, NULL},
        {"S1AP-PDU",            "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"initiatingMessage",   "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"successfulOutcome",   "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"unsuccessfulOutcome", "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"Item",                "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

        {"pduType",             "",                        DICT_NTYPE_BITSET,  DICT_DTYPE_UINT8, false,NULL, NULL},
        {"procedureCode",       "",                        DICT_NTYPE_FIELD,   DICT_DTYPE_UINT8, true, NULL, NULL},
        {"critically",          "",                        DICT_NTYPE_BITSET,  DICT_DTYPE_UINT16,true, NULL, NULL},
        {"valueSize",           "",                        DICT_NTYPE_BITSET,  DICT_DTYPE_UINT16,true, NULL, NULL},

        {"value",               "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

        {"Paging",              "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"UEContextRelease",    "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"UEContextModificationRequest", "",               DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

        {"protocolIEs",               "",                  DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"protocolIE-field",          "",                  DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"protocolIE-SingleContainer","",                  DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

        {"id",                     "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT16,true, NULL, NULL},

        /* ---- */
        {"MME-UE-S1AP-ID",         "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT32,true, NULL, NULL},
        {"ENB-UE-S1AP-ID",         "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT16,true, NULL, NULL},

        /* 2  */
        {"Cause",                  "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"radioNetwork",           "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT8, true, NULL, NULL},

        /* 43 */
        {"UEPagingID",             "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"s-TMSI",                 "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"mMEC",                   "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_HEX16, true, NULL, NULL},
        {"m-TMSI",                 "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_HEX32, true, NULL, NULL},

        /* 46 */
        {"TAIList",                "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

        /* 47 */
        {"TAIItem",                "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"pLMNIdentity",           "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_HEX24, true, NULL, NULL},
        {"tAC",                    "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_HEX16, true, NULL, NULL},
        {"MCC",                    "",                     DICT_NTYPE_BITSET,  DICT_DTYPE_HEX16, true, NULL, NULL},
        {"MNC",                    "",                     DICT_NTYPE_BITSET,  DICT_DTYPE_HEX16, true, NULL, NULL},

        /* 66 */
        {"UEAggregateMaximumBitrate","",                   DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"uEaggregateMaximumBitRateDL","",                 DICT_NTYPE_FIELD,   DICT_DTYPE_UINT32, true, NULL, NULL},
        {"uEaggregateMaximumBitRateUL","",                 DICT_NTYPE_FIELD,   DICT_DTYPE_UINT32, true, NULL, NULL},

        /* 80 */
        {"UEIdentityIndexValue",   "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_HEX16, true, NULL, NULL},

        /* 99 */
        {"UE_S1AP_IDs",            "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"uE-S1AP-ID-pair",        "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

        /* 109 */
        {"CNDomain",               "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT8, true, NULL, NULL},

        {NULL,                  NULL,                      0,                  0,                true, NULL, NULL}
};

#endif
