/*
implement linked list and doubly linked list
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "llist.h"

static int err;

/*
 * create a linked list from an array, by looping though each element, then
 * create a node and add it
 */
llist_t *llist_from_array(void * data, size_t size, size_t len) {
	llist_t *head = malloc(sizeof(llist_t));
	llist_t *ptr = head;
	if (!head) {
		err = LLIST_NOMEM;
		return err;
	}
	head->data = malloc(size);
	if (!head->data) {
		err = LLIST_NOMEM;
		free(head);
		return err;
	}
	//data of new node
	memcpy(head->data, data, size);

	for (int i = 1; i < len; ++i) {
		llist_t *new = malloc(sizeof(llist_t));
		if (!new) {
			err = LLIST_NOMEM;
			return NULL;
		}
		new->data = malloc(size);
		if (!new->data) {
			err = LLIST_NOMEM;
			free(new);
			return NULL;
		}
		memcpy(new->data, data + i*size, size);
		new->next = NULL;
		//point the head to this
		ptr->next = new;
		ptr = new;
	}
	return head;
}

//create the first element in the list with data = data
llist *llist_create(void * data, size_t size) {
	llist_t *head = malloc(sizeof(llist_t));
	if (!head) {
		err = LLIST_NOMEM;
		return NULL;
	}
	head->data = malloc(size);
	if (!head->data) {
		err = LLIST_NOMEM;
		free(head);
		return NULL;
	}
	memcpy(head->data, data, size);
	head->next = NULL;
	return head;
}

//add one data to the end of the list by recursion
int llist_add_to_end(llist_t *head, void *data, size_t size) {
	if (head->next == NULL) {
		llist_t *new = malloc(sizeof(llist_t));
		if (!new) {
			err = LLIST_NOMEM;
			return err;
		}
		new->next = NULL;
		new->data = malloc(size);
		if (!new->data) {
			err = LLIST_NOMEM;
			free(new);
			return err;
		}
		head->next = new;
		
		err = LLIST_OK;
		return err;
	}
	llist_add_to_end(head->next, data, size);
}

/*
add 1 element after the element which has the data equal to `data`
we will know that by invoke the call to `equal` function pointer
*/
int llist_add_after_val(llist_t *head, void *data, size_t size, int (*equal)(const void *, const void *)) {
	if (equal(head->data, data)) {
		//create new node
		llist_t *new = malloc(sizeof(llist_t));
		new->data = malloc(size);
		
		if (!new || !new->data) {
			err = LLIST_NOMEM;
			return err;
		}
		new->next = head->next;
		memcpy(new->data, data, size);
		
		//current node point to new node
		head->next = new;
	}
	//end of the list, no such value
	if (head->next == NULL) {
		err = LLIST_NOVAL;
		return err;
	}
	//recursively call add
	llist_add_after_val(head->next, data, size, equal);
}

int llist_remove_end(llist_t *head) {
	//the element which is near the last element
	if (head->next == NULL) {
		//llist with 1 element
		free(head);
	}
	if (head->next->next == NULL) {
		free(head->next);
	}
	err = LLIST_OK;
	return err;
}

/*
remove the node which has the data equal to data
we will know that by invoke the call to `equal` function pointer
*/
int llist_remove_val(llist_t *head, void *data, size_t size, int(*equal)(const void *, const void *)) {
	//1st node
	if (equal(head->data, data)) {
		err = LLIST_NOVAL;
		return err;
	}
	//the node which is near the node that we need
	if (equal(head->next->data, data)) {
		void *temp = head->next->next;
		free(head->next);
		head->next =temp;
	}
}

/*
 * returns the last node of the list, this could be slow if the list is too long
 * so we avoid using recursion to reduce the number of stack frames 
 * fixme: 
 	create a struct that contains first and last node
 	create 2 global variables in the lib and set it each time
 	altering the list
 */
llist_t *llist_last_node(llist_t *head) {
	llist_t *ptr = head;
	while (ptr->next != NULL) {
		ptr = ptr->next;
	}
	return ptr;
}

//create the first element in the list
dllist_t *dllist_create(void *data) {
	dllist_t *head = malloc(sizeof(dllist_t));
	if (!head) {
		err = DLLIST_NOMEM;
		return NULL;
	}
	head->data = malloc(size);
	if (!head->data) {
		err = DLLIST_NOMEM;
		free(head);
		return NULL;
	}
	memcpy(head->data, data, size);
	//set up ptrs
	head->next = NULL;
	head->prev = NULL;
	
	return head;
}

int dllist_add_to_end(dllist_t *head, void *data, size_t size) {
	if (head->next == NULL) {
		//first node
		dllist_t *new = malloc(sizeof(dllist_t));
		if (!new) {
			err = DDLIST_NOMEM;
			return err;
		}
		new->data = malloc(size);
		if (!new->data) {
			err = DDLIST_NOMEM;
			free(new);
			return err;
		}
		new->prev = head;
		new->next = NULL;
	}
	dllist_add_to_end(head->next, data, size);
	return DDLIST_OK;
}

int dllist_add_after_val(dllist_t *head, void *data, size_t size, int (*equal)(const void *, const void *)) {
	if (equal(head->data, data)) {
		dllist_t *new = malloc(sizeof(dllist_t));
		if (!new) {
			err = DLLIST_NOMEM;
			return err;
		}
		new->data = malloc(size);
		if (!new->data) {
			err = DLLIST_NOMEM;
			free(new);
			return err;
		}
		new->prev = head;
		new->next = head->next;
		
		head->next = new;
		return DDLIST_OK;
	}
	dllist_add_after_val(head->next, data, size, equal);
}
