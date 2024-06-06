#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraylist.h"

arraylist_t * 
arraylist_alloc (int unit) {
    arraylist_t* l;
    l = (arraylist_t*)malloc(sizeof(arraylist_t));
    l->capacity = 10;
    l->length = 0;
    l->unit = unit;
    l->elements = (int*) calloc(l->capacity,l->unit);
    return l;
}

void
arraylist_free (arraylist_t * l, void (* free_element)(void * e)){
    if(free_element != NULL){
        int i;
        for(i = 0; i < l->length; i++){
            void* elem = l->elements + i * l->unit;
            free_element(elem);
        }
    }
    free(l->elements);
    free(l);
}

int 
arraylist_length (arraylist_t * l){
    return l->length;
}

void
arraylist_print (arraylist_t * l, void (* print_element)(void * e)) {
    if(print_element != NULL){
        int i = 0;
        for(i = 0; i < l->length; i++){
            void* elem = l->elements + i * l->unit;
            print_element(elem);
        }
    }
}

void
arraylist_insert_first (arraylist_t * l, void * e){
    if(l->length == l->capacity){
        l->capacity *= 2;
        l->elements = (int*)realloc(l->elements, l->capacity*l->unit);
    }

    for(int i = l->length - 1; i >= 0; i--){
        memcpy(l->elements+(i+1)*l->unit, l->elements+ i * l->unit, l->unit);
    }
    memcpy(l->elements, e, l->unit);
    l->length ++;
}

void
arraylist_insert_last (arraylist_t * l, void * e){
    if(l->length == l->capacity){
        l->capacity *= 2;
        l->elements = (int*)realloc(l->elements, l->unit * l->capacity);
    }
    memcpy(l->elements+l->length*l->unit, e, l->unit);
    l->length++;
}

int
arraylist_remove_first (arraylist_t * l, void * e){
    if(l->length == 0){
        return 0;
    }

    memcpy(e,l->elements,l->unit);
    for(int i = 1; i < l->length; i++){
        memcpy(l->elements+(i-1)*l->unit, l->elements+i * l->unit,l->unit);
    }
    l->length--;
    return 1;
}

int
arraylist_remove_last (arraylist_t * l, void * e) {
    if(l->length == 0){
        return 0;
    }

    memcpy(e,l->elements + (l->length-1) * l->unit, l->unit);

    l->length--;
    return 1;
}

int
arraylist_get (arraylist_t * l, int pos, void * e){
    if(l->length <= pos){
        return 0;
    }

    memcpy(e, l->elements+pos*l->unit,l->unit);
    return 1;
}   

void
arraylist_sort (arraylist_t * l, int (* cmp_elements)(void * e1, void * e2)){
    if (l == NULL || l->elements == NULL || l->length <= 1) {
            return;
        }

    for(int i = 0; i < l->length-1; i++){
        for(int j = 0; j < l->length - i - 1; j++){
            void* elem1 = l->elements + j *l->unit;
            void* elem2 = l->elements + (j+1)*l->unit;

            if(cmp_elements(elem1, elem2) > 0){
                void* temp = malloc(l->unit);
                memcpy(temp, elem1, l->unit);
                memcpy(elem1, elem2, l->unit);
                memcpy(elem2, temp, l->unit);
                free(temp);
            }
        }
    }
}

void
_arraylist_qsort (arraylist_t * l, int (* cmp_elements)(void * e1, void * e2), void * begin, void * end){
    if(begin >= end - l->unit){
        return;
    }
    int unit = l->unit;
    void* t = malloc(unit);
    void* pivot = begin;
    void* lbound = begin + unit;
    void* rbound = end - unit;

    while(lbound <= rbound){
        while(lbound <= end-unit && cmp_elements(lbound, pivot) <= 0){
            lbound += unit;
        }
        while(rbound > begin && cmp_elements(pivot,rbound) < 0){
            rbound -= unit;
        }

        if(lbound <= rbound){
            memcpy(t, lbound, unit);
            memcpy(lbound, rbound, unit);
            memcpy(rbound, t, unit);
            lbound += unit;
            rbound -= unit;
        }
    }

    memcpy(t, rbound, unit);
    memcpy(rbound, pivot, unit);
    memcpy(pivot, t, unit);

    if(rbound != end-unit){
        _arraylist_qsort(l,cmp_elements, begin, rbound+unit);
        _arraylist_qsort(l, cmp_elements, rbound+unit, end);
    }
    else{
        _arraylist_qsort(l,cmp_elements,begin, rbound);
    }
}

void
arraylist_qsort (arraylist_t * l, int (* cmp_elements)(void * e1, void * e2)){
    _arraylist_qsort(l,cmp_elements,l->elements,l->elements+l->length*l->unit);
}