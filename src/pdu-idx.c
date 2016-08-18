#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pdu-idx.h"

/*
 * AVL Tree implementation base on:
 * http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)AvlTree.html
 */

typedef struct avl_node avl_node_t;
struct avl_node {
    avl_node_t *childs[2];
    int         height;
    char       *key;
    void       *data;
};

#define MAX(x,y) ((x)>(y) ? (x) : (y))

static int
avl_get_height(avl_node_t *node)
{
    return node ? node->height : 0;
}

/* recompute height of a node */
static void
avl_fix_height(avl_node_t *node)
{
    int height0 = node->childs[0] ? node->childs[0]->height : 0;
    int height1 = node->childs[1] ? node->childs[1]->height : 0;

    node->height = 1 + (height0 > height1 ? height0 : height1);
}

/*
 *     y            x
 *    / \   <==>   / \
 *   x   C        A   y
 *  / \              / \
 * A   B            B   C
 *
 */
static void
avl_rotate(avl_node_t **root, int d)
{
    avl_node_t *old_root   = *root;
    avl_node_t *new_root   = old_root->childs[d];
    avl_node_t *old_middle = new_root->childs[!d];

    old_root->childs[d]  = old_middle;
    new_root->childs[!d] = old_root;
    *root = new_root;

    /* update heights */
    avl_fix_height((*root)->childs[!d]);  /* old root */
    avl_fix_height(*root);                /* new root */
}

static void
avl_rebalance(avl_node_t **node)
{
    int d;

    if(*node != NULL) {
        for(d = 0; d < 2; d++) {
            /* maybe child[d] is now too tall */
            if(avl_get_height((*node)->childs[d]) > avl_get_height((*node)->childs[!d]) + 1) {
                /* imbalanced! */
                /* how to fix it? */
                /* need to look for taller grandchild of child[d] */
                if(avl_get_height((*node)->childs[d]->childs[d]) > avl_get_height((*node)->childs[d]->childs[!d])) {
                    /* same direction grandchild wins, do single rotation */
                    avl_rotate(node, d);
                } else {
                    /* opposite direction grandchild moves up, do double rotation */
                    avl_rotate(&(*node)->childs[d], !d);
                    avl_rotate(node, d);
                }

                return;   /* avlRotate called avlFixHeight */
            }
        }

        /* update height */
        avl_fix_height(*node);
    }
}

static int
avl_insert(avl_node_t **node, char *key, void  *data)
{
    if (*node == NULL) {
        *node = malloc(sizeof(avl_node_t));

        (*node)->childs[0] = NULL;
        (*node)->childs[1] = NULL;
        (*node)->height    = 1;
        (*node)->key       = key;
        (*node)->data      = data;

        return 1;

    } else if (strcmp((*node)->key, key) == 0) {
        /* element with this key already exists */
        return 0;

    } else {
        /* do the insert in subtree */
        int ichild = strcmp(key, (*node)->key) > 0;
        int rcode  = avl_insert(&(*node)->childs[ichild], key, data);

        avl_rebalance(node);

        return rcode;
    }
}


static int
avl_search(avl_node_t *node, char *key, void **data)
{
    if (node == NULL) {
        return 0;

    } else if (strcmp(node->key, key) == 0) {
        *data = node->data;
        return 1;

    } else {
        int ichild = strcmp(key, node->key) > 0;
        return avl_search(node->childs[ichild], key, data);
    }
}

/*
 * pdu-idx interface implementation
 */
struct pdu_idx {
    avl_node_t *avl;
};

pdu_idx_t *
pdu_idx_create(void)
{
    return calloc(1, sizeof(pdu_idx_t));
}

int
pdu_idx_insert(pdu_idx_t *root, char *key, void  *data)
{
    return avl_insert(&root->avl, key, data);
}

int
pdu_idx_search(pdu_idx_t *root, char *key, void **data)
{
    return avl_search(root->avl, key, data);
}

