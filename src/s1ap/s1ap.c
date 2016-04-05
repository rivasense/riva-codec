#include <byteswap.h>
#include <stdio.h>
#include "s1ap.h"

void s1ap_decode(char *data, uint16_t size, void *context)
{
    osi_s1ap_head_t *head = (void *)data;

    uint16_t critically = bswap_16(head->critval) >> 14;
    uint16_t valsize    = bswap_16(head->critval) & 0xFFF;

    fprintf(stdout,
            "\t PDU code: %u, procedure code: %u, critically: %u, valsize: %u\n",
            head->pdu_code, head->procedure_code, critically, valsize);
}
