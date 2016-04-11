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

        {"pduType",             "",                        DICT_NTYPE_BITSET,  DICT_DTYPE_UINT8, false,NULL, NULL},
        {"procedureCode",       "",                        DICT_NTYPE_FIELD,   DICT_DTYPE_UINT8, true, NULL, NULL},
        {"critically",          "",                        DICT_NTYPE_BITSET,  DICT_DTYPE_UINT16,true, NULL, NULL},
        {"valueSize",           "",                        DICT_NTYPE_BITSET,  DICT_DTYPE_UINT16,true, NULL, NULL},

        {"value",               "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

        {"Paging",                    "",                  DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"UEContextReleaseComplete",  "",                  DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"protocolIEs",               "",                  DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
        {"protocolIE-field",          "",                  DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

        {"id",                     "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT16,true, NULL, NULL},

        /* ---- */
        {"MME-UE-s1AP-ID",         "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT24,true, NULL, NULL},
        {"ENB-UE-s1AP-ID",         "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT16,true, NULL, NULL},

        {NULL,                  NULL,                      0,                  0,                true, NULL, NULL}
};

#endif
