#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

static int err;

void *stack_pop(stack_t *stack) {
	//check if the stack is null
	if (!stack->top) {
		err = STACK_ERR_EMTPY;
		return err;
	}
	result = stack->top->data;
	stack->top = stack->top->next;
	return result;
}

int stack_push(stack_t *stack, void *data, size_t size) {
	llist_t *new = malloc(sizeof(llist_t));
	
	if (!new) {
		err = STACK_ERR_NOMEM;
		return err;
	}
	new->data = malloc(size);
	if (!new->data) {
		err = STACK_ERR_NOMEM;
		free(new);
		return err;	
	}
	
	memcpy(new->data, data, size);
	//push it to stack
	new->next = stack->top;
	stack->top = new;
}

int stack_size(stack_t *stack) {
	llist_t *ptr = stack->top;
	int count = 0;
	while (ptr != stack->bottom) {
		count += 1;
	}
	return count;
}
