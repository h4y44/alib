/*
 * quick sort any type, by creating generic type void *
 * then using a comparing function to compare that type
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

void g_swap(void *a, void *b, size_t size) {
	void *temp = malloc(size);
	memcpy(temp, a, size);
	memcpy(a, b, size);
	memcpy(b, temp, size);
}

//swaps 2 nodes of a linked list by changing the relative references
//since moving large data could be a big cost
void l_swap(dllist_t *a, dllist_t *b) {
	dllist_t *tnext = a->next;
	dllist_t *tprev = a->prev;

	a->next = b->next;
	a->prev = b->prev;

	b->next = (dllist_t *)tnext;
	b->prev = (dllist_t *)tprev;
}

/*
 * size_t size is the size of the actual data which is an element in the array
 */
int g_split(void *arr, size_t size, int l, int h, int (*compare)(const void *, const void *)) {
	int li = l;
	int hi = h - 1;
	int pi = h;
	while (1) {
		while (compare(arr+li*size, arr+pi*size) < 0) {
			++li;
		}
		while (compare(arr+hi*size, arr+pi*size) >= 0) {
			--hi;
		}
		/*
		 * after this, li holds the index of the most right element which is
		 * greater than the pivot, and hi holds the most left element which is
		 * less than the pivot
		 */
		if (li >= hi) {
			break;
		}
		g_swap(arr+li*size, arr+hi*size, size);
	}
	//the last step
	g_swap(arr+li*size, arr+pi*size, size);
	return li;
}

/*
 * the `compare` fucntion should be returned -1 if the first parameter is `less than`
 * the second, 0 if equal and 1 if `greater` than
 */
int g_qsort(void *arr, size_t size, int l, int h, int (*compare)(const void *, const void *)) {
	if (l >= h) {
		return 0;
	}
	int pivot = g_split(arr, size, l, h, compare);
	g_qsort(arr, sizeof(int), l, pivot-1, compare);
	g_qsort(arr, sizeof(int), pivot+1, h, compare);
	return 0;
}

/*
 * split the list into 2 parts
 */
dllist_t *l_split(size_t size, dllist_t *lnode, dllist_t *hnode, int (*compare)(const void *, const void *)) {
	//find the node which is near last node
	dllist_t *hi = hnode->prev;
	dllist_t *li = lnode;
	dllist_t *pi = hnode;
	
	while (1) {
		while (compare(li->data, pi->data) < 0) {
			li = li->next;
		}
		while (compare(pi->data, hi->data) <= 0) {
			hi = hi->prev;
		}
		/*
		 * left most and right most wrong values
		 */
		if ((hi->next == li) || (li == hi)) {
			break;
		}
		//swap it!
		l_swap(li, hi);
	}
	//the last step is to move the pivot to its correct pos
	l_swap(li, pi);
#ifdef __DEBUG
	printf("%p\n%p\n%p\n", li, pi, hi);
#endif
	return pi;
}

/*
 * quick sort on generic type doubly linked list
 * (shit, doing this on a single linked list is way too ineffective)
 */
int l_qsort(size_t size, dllist_t *lnode, dllist_t *hnode, int (*compare)(const void *, const void *)) {
	if ((lnode == hnode) || (hnode->next == lnode)) {
		return 0;
	}
	
	dllist_t *pivot = l_split(size, lnode, hnode, compare);
	l_qsort(size, lnode, pivot, compare); //actually to pivot - 1 (the node which places right before pivot)
	l_qsort(size, pivot, hnode, compare);
	return 0;
}

// compare 2 ints using void pointer to them
int compare(const void *a, const void *b) {
	int a_int = *(int *)a;
	int b_int = *(int *)b;
	return (a_int - b_int);
}

void printout(int arr[], size_t len) {
	for (int i = 0; i<len; ++i) {
		printf("[%d]", arr[i]);
	}
	printf("\n");
}
/*
 * program entrance to test
 */
int main() {
	int arr[] = {1,6,3,7,4};
	printout(arr, 5);
	g_qsort((void *)arr, sizeof(int), 0, 4, compare);
	printout(arr, 5);
}
