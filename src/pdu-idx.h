#ifndef __PDU_IDX_H__
#define __PDU_IDX_H__

typedef struct pdu_idx pdu_idx_t;

pdu_idx_t *
pdu_idx_create(void);

int
pdu_idx_insert(pdu_idx_t *root, char *key, void  *data);

int
pdu_idx_search(pdu_idx_t *root, char *key, void **data);

#endif
