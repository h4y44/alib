/*
algorithms on binary tree
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "btree.h"

static int err;

#ifdef __DEBUG
void printout(btree_t *root) {
	
}
#endif

//create the root of the tree
btree_t *btree_init(void *data, size_t size) {
	btree_t *new = malloc(sizeof(btree_t));
	if (!new) {
		err = BT_ERR_NOMEM;
		return NULL;
	}
	new->data = malloc(size);
	if (!new->data) {
		err = BT_ERR_NOMEM;
		free(new);
		return NULL;
	}
	memcpy(new->data, data, size);
	new->lchild = NULL;
	new->rchild = NULL;
	
	return new;
}

//add one child to the current node
int btree_add_child(btree_t *root, int pos, void *data, size_t size) {
	if (root->lchild && root->rchild) {
		err = BT_ERR_NOCHILD;
		return BT_ERR_NOCHILD;
	}
	
	btree_t *new = malloc(sizeof(btree_t));
	if (!new) {
		err = BT_ERR_NOMEM;
		return err;
	}
	new->data = malloc(size);
	if (!new->data) {
		err = BT_ERR_NOMEM;
		free(new);
		return err;
	}
	memcpy(new->data, data, size);
	new->lchild = NULL;
	new->rchild = NULL;
	
	if (pos == BT_LCHILD) {
		root->lchild = new;
	}
	else if (pos == BT_RCHILD) {
		root->rchild = new;
	}
	return BT_ERR_OK;
}

//count max depth of a tree
int btree_count_max_depth(btree_t *root) {
	//if there is no node
	if (root == NULL) {
		return 0;
	}
	int ldepth = btree_count_max_depth(root->lchild);
	int rdepth = btree_count_max_depth(root->rchild);
	
	if (ldepth >= rdepth) {
		return ldepth +1;
	}
	return rdepth+1;
}


