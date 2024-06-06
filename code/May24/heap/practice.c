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
parent(int i){
    return i/2;
}

int 
left(int i){
    return i*2;
}

int 
right(int i){
    return i*2+1;
}

void *
arr (heap_t * h, int i)
{
	return h->arr + h->usize * i ;
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
	if(h->size == 0){
        return 0;
    }

    memcpy(buf, arr(h,1), h->usize);
    void* temp = malloc(h->usize);
    memcpy(temp, arr(h,1), h->usize);
    memcpy(arr(h,1),arr(h,h->size), h->usize);
    memcpy(arr(h,h->size), temp, h->usize);
    free(temp);
    h->size--;

    int i = 1;
    while((left(i) <= h->size && cmp(h, i, left(i))>0) ||
    (right(i) <= h->size && cmp(h, i, right(i))>0)){
        int r = i;

        if(left(i) <= h->size && cmp(h, r, left(i))>0){
            r = left(i);
        }
        if(right(i) <= h->size && cmp(h, r, right(i)) > 0){
            r = right(i);
        }
        void * temp = malloc(h->usize);
        memcpy(temp, arr(h, r), h->usize);
        memcpy(arr(h,r), arr(h,i), h->usize);
        memcpy(arr(h,i), temp, h->usize);
        i = r;
        free(temp);
    }
    return 1;

}

int
heap_push (heap_t * h, void * buf) 
{
	if(h->size == h->capacity){
        return 0;
    }

    h->size ++;
    memcpy(arr(h,h->size), buf, h->usize);
    int i;
    for(i = h->size; i > 1; i=parent(i)){
        if(cmp(h,parent(i),i) < 0){
            break;
        }
        else{
            void* temp = malloc(h->usize);
            memcpy(temp, arr(h, parent(i)), h->usize);
            memcpy(arr(h, parent(i)), arr(h,i), h->usize);
            memcpy(arr(h,i), temp, h->usize);
            free(temp);
        }
    }
    return 1;
}

int 
heap_remove (heap_t * h, void * buf)

// heap_remove eliminates an element in the heap 
// if the element is equivalent to the element at buf.
// This function returns 1 if an element is removed.
// Otherwise, returns 0.
{
    
}
