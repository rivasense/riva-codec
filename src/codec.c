#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "s1ap/s1ap.h"

#pragma pack(push, 1)

#define PCAP_HDR_MAGIC_IDENT    0xa1b2c3d4
#define PCAP_HDR_MAGIC_SWAPPED  0xd4c3b2a1
#define PCAP_HDR_VER_MAJOR      2
#define PCAP_HDR_VER_MINOR      4

typedef struct pcap_hdr_s
{
    uint32_t magic_number;   /* magic number                                */
    uint16_t version_major;  /* major version number                        */
    uint16_t version_minor;  /* minor version number                        */
    int32_t  thiszone;       /* GMT to local correction                     */
    uint32_t sigfigs;        /* accuracy of timestamps                      */
    uint32_t snaplen;        /* max length of captured packets, in octets   */
    uint32_t network;        /* data link type                              */
} pcap_hdr_t;

typedef struct pcap_rechdr_s
{
    uint32_t ts_sec;         /* timestamp seconds                           */
    uint32_t ts_usec;        /* timestamp microseconds                      */
    uint32_t ilen;           /* number of octets of packet included in file */
    uint32_t olen;           /* origin length of packet                     */
} pcap_rechdr_t;

#pragma pack(pop)

int s1ap_analyze(char *pdata, uint16_t s1ap_off, uint16_t s1ap_sz)
{
    uint16_t cfrom = s1ap_off;
    uint16_t cto   = s1ap_off + s1ap_sz;
    uint16_t rfrom = s1ap_off / 16;
    uint16_t rto   = ((s1ap_off + s1ap_sz) / 16) + ((s1ap_sz % 16) > 0);
    uint16_t ichar = cfrom;

    for (uint32_t irow = rfrom; irow < rto; irow++) {
        fprintf(stdout, "%04x  ", irow << 4);

        for (uint16_t icol = 0; icol < 16; icol++) {
            if (ichar > (irow << 4) + icol) {
                fprintf(stdout, "   ");
            } else {
                fprintf(stdout, "%02x%s", pdata[ichar++] & 0xFF, (icol == 7) ? "  " : " ");
                if (ichar >= cto) {
                    break;
                }
            }
        }
        fprintf(stdout, "\n");
    }

    s1ap_decode(pdata + s1ap_off, s1ap_sz, NULL);

    return 0;
}

int main()
{
    const char *fname = "../s1ap.pcap";
    FILE      *stream = fopen(fname, "rb");
    if (stream == NULL) {
        fprintf(stderr, "can't open %s file for read: %s\n", fname, strerror(errno));
        return -1;
    }

    pcap_hdr_t    pcaphdr;
    pcap_rechdr_t rechdr;
    char          p_body[0xFFFF];
    int           p_cnt;

    if (fread(&pcaphdr, sizeof(pcaphdr), 1, stream) != 1) {
        fprintf(stderr, "can't read %lu bytes from %s file\n", sizeof(pcap_hdr_t), fname);
        return 1;
    }

    for (p_cnt = 1;; p_cnt++) {

        if (fread(&rechdr, sizeof(rechdr), 1, stream) != 1) {
            if (ferror(stream)) /* feof() otherwise */
                fprintf(stderr, "%s: read error\n", fname);
            break;
        }

        if (rechdr.ilen > sizeof(p_body)) {
            fprintf(stderr, "%d packet too long (%u bytes); stop reading\n", p_cnt, rechdr.ilen);
            break;
        }

        if (fread(&p_body, sizeof(char), rechdr.ilen, stream) != rechdr.ilen) {
            if (ferror(stream))
                fprintf(stderr, "%s: read error\n", fname);
            else
                fprintf(stderr, "%s: unexpected eof at %d packet\n", fname, p_cnt);
            break;
        }
        //if (p_cnt == 1) {
        //    s1ap_analyze(p_body, 16 * 4 + 2, 16 + 5);
        //    break;
        //}
        if (p_cnt == 34) {
            s1ap_analyze(p_body, 16 * 4 + 2, 16 * 2 + 8 + 3);
            break;
        }
    }

    fclose(stream);

    return 0;
}
