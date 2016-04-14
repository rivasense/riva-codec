#ifndef __OSI_H__
#define __OSI_H__

#include <stdint.h>

#define OSI_LAYER_PHYSICAL      1
#define OSI_LAYER_DATALINK      2
#define OSI_LAYER_NETWORK       3
#define OSI_LAYER_TRANSPORT     4
#define OSI_LAYER_SESSION       5
#define OSI_LAYER_PRESENTATION  6
#define OSI_LAYER_APPLICATION   7

#define OSI_PROTO_CORRUPT       0x0000001
#define OSI_PROTO_UNKNOWN       0x0000002

#define OSI_PROTO_ETH2          0x2000000
#define OSI_PROTO_VLAN          0x2008100

#define OSI_PROTO_IP4           0x3000800
#define OSI_PROTO_IP6           0x30086DD
#define OSI_PROTO_IP6HOPOPT     0x3100000
#define OSI_PROTO_IP6OPTS       0x310003C
#define OSI_PROTO_IP6ROUTE      0x310002B
#define OSI_PROTO_IP6FRAG       0x310002C
#define OSI_PROTO_IP6NONXT      0x310003B

#define OSI_PROTO_TCP           0x4000006
#define OSI_PROTO_UDP           0x4000011
#define OSI_PROTO_IPIP          0x400005E
#define OSI_PROTO_ETHERIP       0x4000061
#define OSI_PROTO_SCTP          0x4000084

#define OSI_PROTO_GTP           0x4100000

#define PFILTER_APPLY_TRUE                 (   1)
#define PFILTER_APPLY_FALSE                (   0)
#define PFILTER_APPLY_BADHEADERS           (-101)
#define PFILTER_APPLY_BADSIZE              (-102)
#define PFILTER_APPLY_UPROTO               (-103)
#define PFILTER_APPLY_EINTERNAL            (-104)


typedef struct osi_payload_s
{
    /* Payload protocol name as it used in fastshark dissectors */
    char     *payload;
    /* Transport protocol id                                    */
    uint32_t  transport;
    uint16_t  port;
} osi_payload_t;

#include "osi-proto.h"

typedef struct osi_layer_s
{
    uint32_t          proto;         /* OSI protocol id                        */
    uint32_t          proto_above;   /* OSI above protocol id prediction       */
    uint32_t          size;          /* Size in octets for this layer + above  */
    char             *hdr;           /* OSI protocol header                    */
    char             *payload;       /* Payload for this layer, if !SCTP       */
} osi_layer_t;

#define OSI_STACK_SIZE_MAX   8
#define OSI_BUFFER_SIZE_MAX  0xFFFF

typedef struct sctp_chunk_s
{
    int      apply_result;
    uint32_t idx;
    uint32_t payload_proto_id;
    uint16_t offset;
    uint16_t length;
} sctp_chunk_t;

typedef struct osi_packet_s
{
    char          *data;
    uint32_t       dsize;
    osi_layer_t    layers[OSI_STACK_SIZE_MAX + 1];
    sctp_chunk_t **sctp_chunks;
    uint16_t      *sctp_chunks_c;
    uint16_t      *sctp_chunks_sz;
    uint16_t       sctp_chunk_i;
} osi_packet_t;

int osi_rise(osi_packet_t *packet, int layer);

int osi_trace(osi_packet_t *packet, FILE *output);

#endif
