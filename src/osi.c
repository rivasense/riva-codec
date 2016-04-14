#include <byteswap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "osi.h"

static int osi_look_eth2(osi_layer_t *layer, char *data, uint32_t dsize)
{
    if (dsize < sizeof(osi_proto2_eth2_t))
    {
        return PFILTER_APPLY_BADSIZE;
    }

    osi_proto2_eth2_t *eth2 = (void *) data;
    layer->proto   = OSI_PROTO_ETH2;
    layer->size    = dsize;
    layer->hdr     = (void *) eth2;
    layer->payload = (void *)(eth2 + 1);

    uint16_t etype = bswap_16(eth2->etype);
    switch(etype)
    {
    case OSI_PROTO_VLAN & 0xfffff:
        layer->proto_above = OSI_PROTO_VLAN;
        break;

    case OSI_PROTO_IP4 & 0xfffff:
        layer->proto_above = OSI_PROTO_IP4;
        break;

    case OSI_PROTO_IP6 & 0xfffff:
        layer->proto_above = OSI_PROTO_IP6;
        break;

    default:
        layer->proto_above = OSI_PROTO_UNKNOWN;
    }

    return 0;
}

static int osi_look_vlan(osi_layer_t *layer, char *data, uint32_t dsize)
{
    if (dsize < sizeof(osi_proto2_vlan_t))
    {
        return PFILTER_APPLY_BADSIZE;
    }

    osi_proto2_vlan_t *vlan = (void *) data;
    layer->proto   = OSI_PROTO_VLAN;
    layer->size    = dsize;
    layer->hdr     = (void *) vlan;
    layer->payload = (void *)(vlan + 1);

    uint16_t tpid  = bswap_32(vlan->value) & 0xffff;
    switch(tpid)
    {
    case OSI_PROTO_IP4 & 0xfffff:
        layer->proto_above = OSI_PROTO_IP4;
        break;

    case OSI_PROTO_IP6 & 0xfffff:
        layer->proto_above = OSI_PROTO_IP6;
        break;

    default:
        layer->proto_above = OSI_PROTO_UNKNOWN;
    }

    return 0;
}

static int osi_look_ip4(osi_layer_t *layer, char *data, uint32_t dsize)
{
    if (dsize < sizeof(osi_proto3_ip4_t))
    {
        return PFILTER_APPLY_BADSIZE;
    }

    osi_proto3_ip4_t *ip4 = (void *) data;
    layer->proto   = OSI_PROTO_IP4;
    layer->size    = dsize;
    layer->hdr     = (void *) ip4;
    layer->payload = (void *)(data + (ip4->ip_v_hl & 0xf) * 4);

    switch(ip4->ip_p)
    {
    case OSI_PROTO_TCP & 0xff:
        layer->proto_above = OSI_PROTO_TCP;
        break;

    case OSI_PROTO_UDP & 0xff:
        layer->proto_above = OSI_PROTO_UDP;
        break;

    case OSI_PROTO_SCTP & 0xff:
        layer->proto_above = OSI_PROTO_SCTP;
        break;

    default:
        layer->proto_above = OSI_PROTO_UNKNOWN;
    }

    return 0;
}

static int osi_look_ip6(osi_layer_t *layer, char *data, uint32_t dsize)
{
    if (dsize < sizeof(osi_proto3_ip6_t))
    {
        return PFILTER_APPLY_BADSIZE;
    }

    osi_proto3_ip6_t *ip6 = (void *) data;
    layer->proto   = OSI_PROTO_IP6;
    layer->size    = dsize;
    layer->hdr     = (void *) ip6;
    layer->payload = (void *)(ip6 + 1);

    uint8_t ptype = ip6->ip6_nxt;
    uint8_t fstop = 0;
    for (; fstop == 0; )
    {
        switch(ptype)
        {
        case OSI_PROTO_IP6HOPOPT & 0xff:
        {
            osi_proto3_ip6_hbh_dst_t *hop = (void *)layer->payload;
            layer->payload += (hop->extlen + 1) * 8;
            ptype = hop->next;
            break;
        }
        case OSI_PROTO_IP6OPTS & 0xff:
        {
            osi_proto3_ip6_hbh_dst_t *dst = (void *)layer->payload;
            layer->payload += (dst->extlen + 1) * 8;
            ptype = dst->next;
            break;
        }
        case OSI_PROTO_IP6ROUTE & 0xff:
        {
            osi_proto3_ip6_routing_t *rout = (void *)layer->payload;
            layer->payload += (rout->extlen + 1) * 8;
            ptype = rout->next;
            break;
        }
        case OSI_PROTO_IP6FRAG & 0xff:
        {
            osi_proto3_ip6_fragment_t *frag = (void *)layer->payload;
            layer->payload += sizeof(osi_proto3_ip6_fragment_t);
            ptype = frag->next;
            break;
        }
        case OSI_PROTO_IP6NONXT & 0xff:
        {
            ptype = OSI_PROTO_UNKNOWN;
            fstop = 1;
            break;
        }
        default:
            fstop = 1;
            break;
        }
    }

    layer->proto_above = ptype | 0x4000000;

    return 0;
}

static int osi_look_tcp(osi_layer_t *layer, char *data, uint32_t dsize)
{
    if (dsize < sizeof(osi_proto4_tcp_t))
    {
        return PFILTER_APPLY_BADSIZE;
    }

    osi_proto4_tcp_t *tcp = (void *) data;
    layer->proto       = OSI_PROTO_TCP;
    layer->size        = dsize;
    layer->hdr         = (void *) tcp;

    /* tcp hdr size are stored in 0-3 bits of tcp->doff field, counted in 32-bit words */
    layer->payload     = (void *) tcp + ((bswap_16(tcp->doff) >> 12) << 2);

    uint16_t sport = bswap_16(tcp->sport);
    uint16_t dport = bswap_16(tcp->dport);

    if ((dport == 2123) || (sport == 2123) || (dport == 2152) || (sport == 2152) || (dport == 3386) || (sport == 3386))
        layer->proto_above = OSI_PROTO_GTP;
    else
        layer->proto_above = OSI_PROTO_UNKNOWN;

    return 0;
}

static int osi_look_udp(osi_layer_t *layer, char *data, uint32_t dsize)
{
    if (dsize < sizeof(osi_proto4_udp_t))
    {
        return PFILTER_APPLY_BADSIZE;
    }

    osi_proto4_udp_t *udp = (void *) data;
    layer->proto       = OSI_PROTO_UDP;
    layer->size        = dsize;
    layer->hdr         = (void *) udp;
    layer->payload     = (void *)(udp + 1);

    uint16_t sport = bswap_16(udp->sport);
    uint16_t dport = bswap_16(udp->dport);

    if ((dport == 2123) || (sport == 2123) || (dport == 2152) || (sport == 2152) || (dport == 3386) || (sport == 3386))
        layer->proto_above = OSI_PROTO_GTP;
    else
        layer->proto_above = OSI_PROTO_UNKNOWN;

    return 0;
}

static int osi_look_sctp(osi_packet_t *packet, osi_layer_t *layer, char *data, uint32_t dsize)
{
    if (dsize < sizeof(osi_proto4_sctp_t))
    {
        return PFILTER_APPLY_BADSIZE;
    }

    int ichunk = 0;
    osi_proto4_sctp_t *sctp = (void *) data;
    layer->proto       = OSI_PROTO_SCTP;
    layer->size        = dsize;
    layer->hdr         = (void *) sctp;
    layer->payload     = (void *)(sctp + 1);
    layer->proto_above = OSI_PROTO_UNKNOWN;

    while ((layer->payload - layer->hdr) <= (dsize - sizeof(osi_proto4_sctp_chunk_t)))
    {
        osi_proto4_sctp_chunk_t *chunk = (void *)layer->payload;
        uint16_t                 chlen = bswap_16(chunk->length);

        if (chlen < sizeof(osi_proto4_sctp_chunk_t))
            return PFILTER_APPLY_BADHEADERS;

        if ((layer->payload - layer->hdr) + chlen > dsize)
            return PFILTER_APPLY_BADHEADERS;

        if (chunk->type == 0)  /* DATA chunk */
        {
            osi_proto4_sctp_chunk_data_t *chunk_data = (void *) chunk;

            if ((layer->payload - layer->hdr) + sizeof(osi_proto4_sctp_chunk_data_t) > dsize)
                return PFILTER_APPLY_BADHEADERS;

            /* insert a new record to sctp_chunks array */
            if (*packet->sctp_chunks_c == *packet->sctp_chunks_sz)
            {
                *packet->sctp_chunks_sz = *packet->sctp_chunks_sz + 1;
                *packet->sctp_chunks = realloc(*packet->sctp_chunks, sizeof(sctp_chunk_t) * (*packet->sctp_chunks_sz));
            }
            (*packet->sctp_chunks)[*packet->sctp_chunks_c].apply_result = 1;
            (*packet->sctp_chunks)[*packet->sctp_chunks_c].length = chlen - sizeof(osi_proto4_sctp_chunk_data_t);
            (*packet->sctp_chunks)[*packet->sctp_chunks_c].offset = (layer->payload + sizeof(osi_proto4_sctp_chunk_data_t) - packet->data);
            (*packet->sctp_chunks)[*packet->sctp_chunks_c].payload_proto_id = bswap_32(chunk_data->payload_id);
            (*packet->sctp_chunks)[*packet->sctp_chunks_c].idx = ichunk;

            *packet->sctp_chunks_c = *packet->sctp_chunks_c + 1;
        }

        ichunk++;

        layer->payload += chlen;
        if (chlen % sizeof(osi_proto4_sctp_chunk_t)) {
            layer->payload += sizeof(osi_proto4_sctp_chunk_t) - (chlen % sizeof(osi_proto4_sctp_chunk_t));
        }
    };

    return 0;
}

static int osi_look_gtp(osi_layer_t *layer, char *data, uint32_t dsize)
{
    if (dsize < sizeof(osi_proto4_gtp_t))
    {
        return PFILTER_APPLY_BADSIZE;
    }

    osi_proto4_gtp_t *gtp = (void *) data;
    layer->proto          = OSI_PROTO_GTP;
    layer->size           = dsize;
    layer->hdr            = (void *) gtp;
    layer->payload        = NULL; // Don't care about next proto
    layer->proto_above    = OSI_PROTO_UNKNOWN;

    return 0;
}

static int osi_rise_step(osi_packet_t *packet)
{
    int il, rcode = 0;
    osi_layer_t *olayer = NULL;

    for (il = 0; packet->layers[il].proto != 0; il++);

    if (il == OSI_STACK_SIZE_MAX)
    {
        /* too deep */
        return PFILTER_APPLY_BADHEADERS;

    } else if (il == 0)
    {
        olayer = &packet->layers[0];
        rcode  = osi_look_eth2(olayer, packet->data, packet->dsize);

    } else if ((packet->layers[il-1].proto >> 24) == 0)
    {
        /* unknown/corrupted protocol at last layer */
        return PFILTER_APPLY_UPROTO;

    } else
    {
        olayer               = &packet->layers[il];
        osi_layer_t *p_layer = &packet->layers[il-1];
        char        *p_data  = p_layer->payload;
        uint32_t     p_size  = p_layer->size - (p_layer->payload - p_layer->hdr);

        switch(p_layer->proto_above)
        {
        case OSI_PROTO_VLAN:
            rcode = osi_look_vlan(olayer, p_data, p_size);
            break;

        case OSI_PROTO_IP4:
            rcode = osi_look_ip4(olayer, p_data, p_size);
            break;

        case OSI_PROTO_IP6:
            rcode = osi_look_ip6(olayer, p_data, p_size);
            break;

        case OSI_PROTO_TCP:
            rcode = osi_look_tcp(olayer, p_data, p_size);
            break;

        case OSI_PROTO_UDP:
            rcode = osi_look_udp(olayer, p_data, p_size);
            break;

        case OSI_PROTO_SCTP:
            rcode = osi_look_sctp(packet, olayer, p_data, p_size);
            break;

        case OSI_PROTO_GTP:
            rcode = osi_look_gtp(olayer, p_data, p_size);
            break;

        case OSI_PROTO_UNKNOWN:
            /* some prediction logic */
            memset(olayer, 0, sizeof(osi_layer_t));
            olayer->proto = OSI_PROTO_UNKNOWN;
            break;

        default:
            /* unexpected value      */
            return PFILTER_APPLY_EINTERNAL;
        }
    }

    if (rcode < 0)
    {
        memset(olayer, 0, sizeof(osi_layer_t));
        olayer->proto = OSI_PROTO_CORRUPT;
        return rcode;
    }

    return olayer->proto;
}

int osi_rise(osi_packet_t *packet, int layer)
{
    int lproto = 0, pproto = 0;

    do {
        if (lproto != 0)
            pproto = lproto;
        lproto = osi_rise_step(packet);

    } while ( (lproto > 0)             &&
              ((lproto >> 24) > 0)     &&
              ((lproto >> 24) <= layer)  );

    if (lproto < 0)
        return lproto;

    else if ((lproto >> 24) > 0)
        return lproto >> 24;

    else if (lproto == OSI_PROTO_UNKNOWN)
        return pproto;

    else
        return PFILTER_APPLY_EINTERNAL;
}

int osi_trace(osi_packet_t *packet, FILE *output)
{
    int il;
    for (il = 0; (packet->layers[il].proto != 0) && (il < OSI_STACK_SIZE_MAX); il++)
    {
        osi_layer_t *olayer = &packet->layers[il];

        if (olayer->proto == OSI_PROTO_ETH2)
        {
            osi_proto2_eth2_t *eth2 = (void *) olayer->hdr;
            uint16_t etype = bswap_16(eth2->etype);

            fprintf(output,
                    "\t Ethernet II: SRC MAC: %02x:%02x:%02x:%02x:%02x:%02x  DST MAC: %02x:%02x:%02x:%02x:%02x:%02x  TYPE: 0x%x\n",
                    eth2->src[0], eth2->src[1], eth2->src[2], eth2->src[3], eth2->src[4], eth2->src[5],
                    eth2->dst[0], eth2->dst[1], eth2->dst[2], eth2->dst[3], eth2->dst[4], eth2->dst[5],
                    etype);

        } else if (olayer->proto == OSI_PROTO_VLAN)
        {
            osi_proto2_vlan_t *vlan = (void *) olayer->hdr;
            uint16_t tpid = bswap_32(vlan->value) & 0xffff;
            uint16_t tci  = bswap_32(vlan->value) >> 16;
            fprintf(output,
                    "\t VLAN: TPID: 0x%x, PCP: %u, DEI: %u, VID: %u\n",
                    tpid, tci >> 13, (tci >> 12) & 1, tci & 0xfff);

        } else if (olayer->proto == OSI_PROTO_IP4)
        {
            osi_proto3_ip4_t   *ip4 = (void *) olayer->hdr;
            uint8_t ip4_ver = ip4->ip_v_hl >> 4;
            uint8_t ip4_hl  = ip4->ip_v_hl &  0xf;

            fprintf(output,
                    "\t IPv4: v:%u, hl:%u, proto: %u, src: %d.%d.%d.%d, dst: %d.%d.%d.%d\n",
                    ip4_ver, ip4_hl * 4, ip4->ip_p,
                    ip4->ip_src[0], ip4->ip_src[1], ip4->ip_src[2], ip4->ip_src[3],
                    ip4->ip_dst[0], ip4->ip_dst[1], ip4->ip_dst[2], ip4->ip_dst[3]);

        } else if (olayer->proto == OSI_PROTO_IP6)
        {
            osi_proto3_ip6_t *ip6 = (void *) olayer->hdr;
            uint8_t  ip6_ver = ip6->ip6_v_tc_fl >> 28;
            uint8_t  ip6_tc  = (ip6->ip6_v_tc_fl >> 20) & 0xff;
            uint32_t ip6_fl  = bswap_32(ip6->ip6_v_tc_fl & 0xfffff);

            fprintf(output,
                    "\t IPv6: v:%u, tc:%u, fl: %u, src: %x:%x:%x:%x:%x:%x:%x:%x, dst: %x:%x:%x:%x:%x:%x:%x:%x\n",
                    ip6_ver, ip6_tc, ip6_fl,

                    bswap_16(ip6->ip6_src[0]), bswap_16(ip6->ip6_src[1]), bswap_16(ip6->ip6_src[2]), bswap_16(ip6->ip6_src[3]),
                    bswap_16(ip6->ip6_src[4]), bswap_16(ip6->ip6_src[5]), bswap_16(ip6->ip6_src[6]), bswap_16(ip6->ip6_src[7]),

                    bswap_16(ip6->ip6_dst[0]), bswap_16(ip6->ip6_dst[1]), bswap_16(ip6->ip6_dst[2]), bswap_16(ip6->ip6_dst[3]),
                    bswap_16(ip6->ip6_dst[4]), bswap_16(ip6->ip6_dst[5]), bswap_16(ip6->ip6_dst[6]), bswap_16(ip6->ip6_dst[7])
                  );

        } else if (olayer->proto == OSI_PROTO_TCP)
        {
            osi_proto4_tcp_t *tcp = (void *) olayer->hdr;

            fprintf(output,
                    "\t TCP: sport: %u, dport: %u\n",
                    bswap_16(tcp->sport), bswap_16(tcp->dport));

        } else if (olayer->proto == OSI_PROTO_UDP)
        {
            osi_proto4_udp_t *udp = (void *) olayer->hdr;

            fprintf(output,
                    "\t UDP: sport: %u, dport: %u\n",
                    bswap_16(udp->sport), bswap_16(udp->dport));

        } else if (olayer->proto == OSI_PROTO_SCTP)
        {
            osi_proto4_sctp_t *sctp = (void *) olayer->hdr;

            fprintf(output,
                    "\t SCTP: sport: %u, dport: %u, offset: %u\n",
                    bswap_16(sctp->sport), bswap_16(sctp->dport), (uint32_t)(olayer->payload - olayer->hdr));

            int ichunk;
            for (ichunk = 0; ichunk < *packet->sctp_chunks_c; ichunk++)
                fprintf(stdout,
                       "\t\t DATA chunk %d (abs %d): off: %u, len: %u, pload id: %u, apply: %d\n",
                       ichunk,
                       (*packet->sctp_chunks)[ichunk].idx,
                       (*packet->sctp_chunks)[ichunk].offset,
                       (*packet->sctp_chunks)[ichunk].length,
                       (*packet->sctp_chunks)[ichunk].payload_proto_id,
                       (*packet->sctp_chunks)[ichunk].apply_result);

        } else if (olayer->proto == OSI_PROTO_GTP)
        {
            osi_proto4_gtp_t *gtp = (void *) olayer->hdr;

            fprintf(output, "\t GTP: teid: %x\n", bswap_32(gtp->teid));
        }

    }

    fflush(output);

    return 0;
}
