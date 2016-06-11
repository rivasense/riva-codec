#ifndef __S1AP_DICT_H__
#define __S1AP_DICT_H__

#include "../pdu.h"
#include "s1ap_proto_ies.h"

extern struct dict_node   dict_nodes[];

extern s1ap_pie_t         s1ap_pies[];
extern const size_t       s1ap_sz;


typedef struct s1ap_proccode_s {
    uint8_t  id;
    char    *name;
} s1ap_proccode_t;

extern s1ap_proccode_t    s1ap_proccodes[];
extern const size_t       s1ap_proccodes_sz;

#endif
