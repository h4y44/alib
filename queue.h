#include "llist.h"

enum queue_err {
	QUEUE_ERR_NOMEM,
	QUEUE_ERR_EMPTY
};

typedef struct queue_t {
	llist_t *in;
	llist_t *out;
} queue_t;

llist_t *queue_pop(queue_t *);
int queue_push(queue_t *, void *, size_t);
int queue_size(queue_t *);
