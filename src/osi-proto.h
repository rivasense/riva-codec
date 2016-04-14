#ifndef __OSI_PROTO_H__
#define __OSI_PROTO_H__

#include <stdint.h>

#pragma pack(push, 1)


/* VLAN protocol (Ethernet I + 802.1Q (VLAN) tag)
 */
typedef struct osi_proto2_eth1_vlan_s
{
    uint64_t  preamble_sfd;    /* Preamble + Start Frame Delimiter                 */
    uint8_t   dst[6];          /* Destination MAC                                  */
    uint8_t   src[6];          /* Source MAC                                       */
    uint16_t  tpid;            /* TPID (0x8100 for VLAN)                           */
    uint16_t  tci;             /* Tag control information                          */
    uint16_t  etype;           /* Ethernet Type/Size                               */
                               /* <= 1500 - size of the payload in octets          */
                               /* >= 1536 - EtherType, need to find Frame Checksum */
} osi_proto2_eth1_vlan_t;


/* Ethernet II: http://en.wikipedia.org/wiki/Ethernet_II#Ethernet_II
 */
typedef struct osi_proto2_eth2_s
{
    uint8_t  dst[6];           /* Destination MAC                                  */
    uint8_t  src[6];           /* Source MAC                                       */
    uint16_t etype;            /* EtherType                                        */
} osi_proto2_eth2_t;


/* 802.1Q (VLAN): http://en.wikipedia.org/wiki/IEEE_802.1Q
 */
typedef struct osi_proto2_vlan_s
{
    uint32_t  value;           /* TPID (etype) + TCI                               */
} osi_proto2_vlan_t;


/* IPv4: http://en.wikipedia.org/wiki/IPv4#Header
 */
typedef struct osi_proto3_ip4_s
{
    uint8_t  ip_v_hl;          /* combines ip_v and ip_hl                          */
    uint8_t  ip_tos;
    uint16_t ip_len;
    uint16_t ip_id;
    uint16_t ip_off;
    uint8_t  ip_ttl;
    uint8_t  ip_p;
    uint16_t ip_sum;
    uint8_t  ip_src[4];
    uint8_t  ip_dst[4];
} osi_proto3_ip4_t;


/* IPv6: http://en.wikipedia.org/wiki/IPv6_packet#Fixed_header
 */
typedef struct osi_proto3_ip6_s
{
    uint32_t ip6_v_tc_fl;           /* version, traffic class, flow label           */
    uint16_t ip6_pl;                /* payload length                               */
    uint8_t  ip6_nxt;               /* next header                                  */
    uint8_t  ip6_hl;                /* hop limit                                    */
    uint16_t ip6_src[8];            /* source address                               */
    uint16_t ip6_dst[8];            /* destination address                          */
} osi_proto3_ip6_t;

/* IPv6: http://en.wikipedia.org/wiki/IPv6_packet#Hop-by-hop_options_and_destination_options
 */
typedef struct osi_proto3_ip6_hh_dst_s
{
    uint8_t  next;                  /* next header type                             */
    uint8_t  extlen;                /* length in 64-bit words, w/o the first 64 bit */
    uint8_t  padding[6];
} osi_proto3_ip6_hbh_dst_t;

/* IPv6: http://en.wikipedia.org/wiki/IPv6_packet#Routing
 */
typedef struct osi_proto3_ip6_routing_s
{
    uint8_t  next;                  /* next header type                             */
    uint8_t  extlen;                /* length in 64-bit words, w/o the first 64 bit */
    uint8_t  rtype;                 /* routing type (1, 2)                          */
    uint8_t  segleft;               /* segments left                                */
    uint8_t  padding[4];
} osi_proto3_ip6_routing_t;

/* IPv6: http://en.wikipedia.org/wiki/IPv6_packet#Fragment
 */
typedef struct osi_proto3_ip6_fragment_s
{
    uint8_t  next;                  /* next header type                             */
    uint8_t  reserved;              /* zeroes                                       */
    uint16_t off_m;                 /* offset + M flag                              */
    uint32_t ident;                 /* identification                               */
} osi_proto3_ip6_fragment_t;



/* UDP: http://en.wikipedia.org/wiki/User_Datagram_Protocol#Packet_structure
 */
typedef struct osi_proto4_udp_s
{
    uint16_t sport;
    uint16_t dport;
    uint16_t len;
    uint16_t checksum;
} osi_proto4_udp_t;


/* TCP: http://en.wikipedia.org/wiki/Transmission_Control_Protocol#TCP_segment_structure
 */
typedef struct osi_proto4_tcp_s
{
    uint16_t sport;
    uint16_t dport;
    uint32_t seqnum;         /* Sequence number                                     */
    uint32_t acknum;         /* Acknowledgment number (if ACK set)                  */

    uint16_t doff;           /* Data offset + Flags field                           */
    uint16_t wsize;          /* Window size                                         */
    uint16_t checksum;
    uint16_t urgent;         /* Urgent pointer (if URG set)                         */
} osi_proto4_tcp_t;


/* SCTP: http://en.wikipedia.org/wiki/SCTP_packet_structure
 */
typedef struct osi_proto4_sctp_s
{
    uint16_t sport;
    uint16_t dport;
    uint32_t vtag;
    uint32_t checksum;
} osi_proto4_sctp_t;

typedef struct osi_proto4_sctp_chunk_s
{
    uint8_t  type;
    uint8_t  flags;
    uint16_t length;
} osi_proto4_sctp_chunk_t;

typedef struct osi_proto4_sctp_chunk_data_s
{
    uint8_t  type;
    uint8_t  flags;
    uint16_t length;
    uint32_t tsn;
    uint16_t stream_id;
    uint16_t stream_seq;
    uint32_t payload_id;
} osi_proto4_sctp_chunk_data_t;


/* GTP v1/v2: http://en.wikipedia.org/wiki/GPRS_Tunnelling_Protocol
 */
typedef struct osi_proto4_gtp_s
{
    uint8_t  flags;          /* 0-2: version; 1 for v1; 2 for v2                    */
                             /*   3: protocol type         / piggybacking           */
                             /*   4: none                  / TEID flag              */
                             /*   5: extension header flag / none                   */
                             /*   6: sequence number flag  / none                   */
                             /*   7: N-PDU number flag     / none                   */
    uint8_t  type;           /* Message type                                        */
    uint16_t length;         /* Payload (total ?) length                            */
    uint32_t teid;           /* TEID                                                */
    /* ....       */
    /* the rest of protocol fields is differ from v1 to v2 and was skipped          */
} osi_proto4_gtp_t;

#pragma pack(pop)

#endif
