#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

heap_t* heap_create(int capacity, size_t usize, int(*cmp)(void * e1,void * e2)){
    heap_t* h = (heap_t*)malloc(sizeof(heap_t));
    h->capacity = capacity;
    h->size = 0;
    h->usize = usize;
    h->cmp = cmp;
    h->arr = (char*)calloc(capacity+1,usize);
    return h;
}

void heap_free(heap_t* h){
    if(h != NULL){
        free(h->arr);
        free(h);
    }
}

int heap_size (heap_t* h){
    return h->size;
}

int parent(int i){
    return i/2;

}

int left(int i){
    return i*2;
}

int right(int i){
    return i*2+1;
}

void* arr(heap_t *h, int i ){
    return h->arr+i*h->usize;
}    

void swap(heap_t* h, int a, int b){
    char* temp = malloc(h->usize);
    memcpy(temp, arr(h, a), h->usize);
    memcpy(arr(h,a), arr(h,b), h->usize);
    memcpy(arr(h,b), temp, h->usize);
    free(temp);
}

int cmp(heap_t*h, int a, int b){
    return(h->cmp(arr(h,a), arr(h,b)));
}    

int heap_pop(heap_t* h, void* buf){
    if(h->size == 0){
        return 0;
    }

    memcpy(buf, arr(h,1), h->usize);

    swap(h, 1, h->size);
    h->size --;

    int i = 1;
    while((left(i) <= h->size && cmp(h, i, left(i)) > 0) || (right(i) <= h->size && cmp(h, i, right(i)) > 0)){
        int r = i;

        if(left(i) <= h->size && cmp(h, r, left(i)) > 0){
            r = left(i);
        }  
        if(right(i) <= h->size && cmp(h, r, right(i))>0){
            r = right(i);
        }

        swap(h, i, r);
        i = r;
    }
    return 1;
}       

int heap_push(heap_t * h, void * buf){
    if(h->size == h->capacity){
        return 0;
    }

    h->size ++;
    memcpy(arr(h,h->size),buf, h->usize);

    for(int i= h->size; i > 1; i = parent(i)){
        if(cmp(h, parent(i), i) < 0){
            break;
        }
        else{
            swap(h, i, parent(i));
        }
    }
    return 1;
}

int 
heap_remove (heap_t * h, void * buf){
    int i;
    for(i = 1; i <= h->size; i++){
        if(h->cmp(arr(h,i),buf) == 0)
            break;
    }

    if(i > h->size){
        return 0;
    }

    swap(h, i, h->size);
    h->size--;

    i = 1;
    while((left(i) <= h->size && cmp(h, i, left(i))> 0) || (right(i) <= h->size && cmp(h, i, right(i))> 0)){
        int r = i;

        if(left(i) <= h->size && cmp(h, r, left(i))> 0){
            r = left(i);
        }
        if(right(i) <= h->size && cmp(h, r, right(i))> 0){
            r = right(i);
        }
        swap(h, i, r);

        i = r;

    }

    return 1;
}