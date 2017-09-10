/*
linked list, doubly linked list with generic pointer type
data in generic type is a combination of a void pointer
and size of that data, which has type of size_t
*/

#ifndef __LLIST_H__
#define __LLIST_H__
enum llist_err {
	LLIST_OK, //no error
	LLIST_NOMEM, //no memory left
	LLIST_NOVAL //no such value
};

enum dllist_err {
	DLLIST_OK,
	DLLIST_NOMEM,
	DLLIST_NOVAL
};

typedef struct llist_t {
	void *data;
	struct llist_t *next;
} llist_t;

typedef struct dllist_t {
	void *data;
	struct dllist_t *next, *prev;
} dllist_t;

/*
function prototypes
*/

llist_t *llist_from_array(void *data, size_t size, size_t len);
llist_t *llist_create(void *, size_t);
llist_t *llist_last_node(llist_t *);
int llist_add_to_end(llist_t *, void *, size_t);
int llist_add_after_val(llist_t *, void *, size_t);
int llist_remove_end(llist_t *);
int llist_remove_val(llist_t *, void *, size_t);

int dllist_create(void *, size_t);
int dllist_add_to_end(dllist_t *, void *, size_t);
int dllist_add_after_val(dllist_t *, void *, size_t);

#endif
