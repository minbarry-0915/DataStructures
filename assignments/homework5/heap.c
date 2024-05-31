#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

heap_t *
heap_create (int capacity, size_t usize, int (* cmp)(void *e1, void *e2)) 
{
	heap_t * h = malloc(sizeof(heap_t)) ;
	h->arr = calloc(capacity + 1, usize) ;
	h->capacity = capacity ;
	h->size = 0 ;
	h->usize = usize ;
	h->cmp = cmp ;
	return h ;
}

void
heap_free (heap_t * h) 
{
	free(h->arr) ;
	free(h) ;
}

int
heap_size (heap_t * h)
{
	return h->size ;
}

int
parent (int i) 
{ 
	return i / 2 ;
}

int
left (int i) 
{ 
	return i * 2 ; 
}

int
right (int i) 
{ 
	return i * 2 + 1 ; 
}

void *
arr (heap_t * h, int i)
{
	return h->arr + h->usize * i ;
}

void
swap (heap_t * h, int a, int b)
{
	char * tmp = (char *) malloc(h->usize) ;
	memcpy(tmp, arr(h, a), h->usize) ;
	memcpy(arr(h, a), arr(h, b), h->usize) ;
	memcpy(arr(h, b), tmp, h->usize) ;
	free(tmp) ;
}

int
cmp (heap_t * h, int a, int b)
{
	return h->cmp(h->arr + a * h->usize, h->arr + b * h->usize) ;
}

int
heap_top (heap_t * h, void * buf)
{
	if (h->size == 0)
		return 0 ;
	memcpy(buf, arr(h, 1), h->usize) ;
	return 1 ;
}

int
heap_pop (heap_t * h, void * buf)
{
	/* FIXME: fix this function for Task 1 */

	if (h->size == 0)
		return 0 ;
	
	if (h->size < h->capacity/4){
		printf("\nRemaining elements: %d, The quarter of the capacity: %d\n", h->size, h->capacity/4);
		printf("Halving the capacity...\n");
		h->capacity = h->capacity / 2;
		h->arr = realloc(h->arr, (h->capacity+1)*h->usize);
		printf("Current Heap Capacity: %d\n\n", h->capacity);
	}

	memcpy(buf, arr(h, 1), h->usize) ;

	//가장 마지막에 있던 원소가 제일 앞으로   옴
	swap(h, 1, h->size) ;
	h->size-- ;

	//트리 구조 재정렬
	int i = 1 ;
	//자식들 보다 클때
	while ((left(i) <= h->size && cmp(h, i, left(i)) > 0) || 
		right(i) <= h->size && cmp(h, i, right(i)) > 0) {

		int r = i ;
		if (left(i) <= h->size && cmp(h, r, left(i)) > 0) {
			r = left(i) ;
		}
		if (right(i) <= h->size && cmp(h, r, right(i)) > 0) {
			r = right(i) ;
		}

		swap(h, i, r) ;

		i = r ;
	}
	return 1 ;
}

int
heap_push (heap_t * h, void * buf) 
{
	/* FIXME: fix this function for Task 1 */

	if (h->size == h->capacity) { 
		printf("\nHeap is full: Extending Current Capacity ... \n");
		h->capacity *= 2;
		h->arr = realloc(h->arr, (h->capacity+1)*h->usize);
		printf("Current Heap Capacity: %d\n\n", h->capacity);
	}

	h->size += 1 ;
	memcpy(arr(h, h->size), buf, h->usize) ;

	int i ;
	for (i = h->size ; i > 1 ; i = parent(i)) {
		if (cmp(h, parent(i), i) < 0) {
			break ;
		}
		else {
			swap(h, parent(i), i) ;
		}
	}

	return 1 ;
}

int 
heap_remove (heap_t * h, void * buf)

// heap_remove eliminates an element in the heap 
// if the element is equivalent to the element at buf.
// This function returns 1 if an element is removed.
// Otherwise, returns 0.

{
	/*TODO: Task 2*/
	int index;
	for(index = 1; index <= h->size; index++){
		if(h->cmp(arr(h,index),buf) == 0){
			//printf("found\n");
			break;
		}
	}
	if(index > h->size){
		printf("Fail to Find\n");
		return 0;
	}
	
	swap(h, index, h->size);
	h->size--;

	//트리 구조 재정렬: 왼쪽이 무조건 오른쪽 보다 작게 만들어야됨
	int i = 1 ;
	//자식들 보다 클때
	while ((left(i) <= h->size && cmp(h, i, left(i)) > 0) || 
		right(i) <= h->size && cmp(h, i, right(i)) > 0) {
		
		int r = left(i) ;
		if (right(i) <= h->size && cmp(h, left(i), right(i)) > 0) {
			r = right(i) ;
		}

		swap(h, i, r) ;

		i = r ;
	}
	return 1 ;
}
