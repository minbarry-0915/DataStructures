#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"

slist_t *
slist_create (int capacity, size_t usize, int (* cmp)(void *e1, void *e2)) 
{
    slist_t* t = (slist_t *)malloc(sizeof(slist_t));
    t->arr = (char*)calloc(capacity, usize);
    t->capacity = capacity;
    t->usize = usize;
    t->cmp = cmp;
    t->size = 0;
}

void
slist_free (slist_t * h) 
{
	free(h->arr);   
    free(h);
}

int
slist_size (slist_t * h)
{
	return h->size;
}

int
cmp (slist_t * h, int a, int b)
{
	return h->cmp(h->arr+a*h->usize, h->arr+b*h->usize);
}

int
slist_top (slist_t * h, void * buf)
{
    if(h->size == 0){
        return 0;
    }
	memcpy(buf,h->arr,h->usize);
    return 1;
}

int
slist_pop (slist_t * h, void * buf)
{
    if(h->size == 0){
        return 0;
    }

    memcpy(buf, h->arr, h->usize);

    for(int i = 0; i < h->size-1; i++){
        memcpy(h->arr+i*h->usize, h->arr+(i+1)*h->usize, h->usize);
    }
    h->size --;
    return 1;
}

int
slist_push (slist_t * h, void * buf) 
{
    if(h->size == h->capacity){
        return 0;
    }

    int p = 0;
    for(p= 0; p < h->size; p ++){
        if(h->cmp(h->arr+p*h->usize,buf) > 0){
            break;
        }
    }

    //p뒤에있는애들 한칸씩 미루기
    for(int i = h->size; i > p; i--){
        memcpy(h->arr + i * h->usize, h->arr+(i-1)* h->usize, h->usize);
    }

    memcpy(h->arr + p * h->usize, buf, h->usize);
    h->size ++;
    return 1;
}

int slist_reverse (slist_t * h){
    if(h->size == 0){
        return 0;
    }

    void* reverse = (char*)calloc(h->size,h->usize);
    for(int i = 0; i < h->size; i++){
        memcpy(reverse + i * h->usize, h->arr + (h->size-1-i)*h->usize,h->usize);
    }
    h->arr = reverse;
    return 1;
}