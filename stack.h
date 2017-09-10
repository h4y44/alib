#include "llist.h"

enum stack_err {
	STACK_ERR_NOMEM,
	STACK_ERR_EMPTY
};

typedef struct stack_t {
	llist_t *top;
	llist_t *bottom;
} stack_t;

void *stack_pop(stack_t *);
int stack_push(stack_t *, void *, size_t);
int stack_size(stack_t *);
