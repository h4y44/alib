#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

/*
 * insertion sort algorithm on linked list
 */
int ssort(llist_t *list, size_t size, int (*compare)(const void *, const void *)) {
	llist_t *sorted = list;
	llist_t *usorted = list->next;
	
	while (usorted != NULL) {
		for (llist_t *ptr = list; ptr != sorted; ptr = ptr->next) {
			if (compare(ptr->data, usorted->data) < 0) {
				
			}
		}
		usorted = usorted->next;
	}
} 
