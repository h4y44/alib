/*
implement binary tree
*/

#ifndef __BTREE_H__
#define __BTREE_H__

enum bintree {
	BT_ERR_NOMEM;
	BT_ERR_NOCHILD;
	BT_ERR_OK;
	BT_LCHILD;
	BT_RCHILD;
};

typedef struct btree_t {
	void *data;
	struct btree_t *lchild, *rchild;
} btree_t;

/*
function prototypes
*/

#ifdef __DEBUG
void printout(btree_t *);
#endif

btree_t *btree_init(void *, size_t);
int btree_add_child(btree_t *, int, void *, size_t);
int btree_count_max_depth(btree_t *, int);
int btree_balance(btree_t *);

#endif
