#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraylist.h"

arraylist_t * 
arraylist_alloc (int unit) 
{
	arraylist_t* l = (arraylist_t*)malloc(sizeof(arraylist_t));
    l->capacity = 10;
    l->length = 0;
    l->unit = unit;
    l->elements = (int*)calloc(l->capacity,l->unit);
    return l;
}

void
arraylist_free (arraylist_t * l, void (* free_element)(void * e)) 
{
	if(free_element != 0x0){ //free함수를 제공했을때,
        int i;
        for(i=0; i<l->length; i++){
            void * elem = l->elements + l->unit * i;
            free_element(elem);
        }
    }
}

int 
arraylist_length (arraylist_t * l)
{
	return l->length;
}

void
arraylist_print (arraylist_t * l, void (* print_element)(void * e)) 
{
	int i;
    for(i = 0; i < l->length; i++){
        void* element = l->elements + i * l->unit;
        print_element(element);
    }
}

void
arraylist_insert_first (arraylist_t * l, void * e)
{
	if(l->capacity == l->length){
        l->capacity *= 2;
        l->elements = (int*)realloc(l->elements, (size_t)l->capacity*l->unit);
    }

    int i;
    for(i = l->length - 1; i >= 0; i--){
        memcpy(l->elements + (i+1) * l->unit, l->elements+i*l->unit, l->unit);
    }
    memcpy(l->elements, e, l->unit);
    l->length++;
}

void
arraylist_insert_last (arraylist_t * l, void * e)
{
	if(l->capacity == l->length){
        l->capacity *= 2;
        l->elements = (int*)realloc(l->elements, (size_t)l->capacity*l->unit);
    }

    memcpy(l->elements+l->length*l->unit, e, l->unit);
    l->length++;
}

int
arraylist_remove_first (arraylist_t * l, void * e) 
{
	if(l->length == 0){
        return 1;
    }

    memcpy(l->elements, e, l->unit);
    int i;
    for(i = 1; i < l->length; i++){
        memcpy(l->elements+(i-1)*l->unit, l->elements+i*l->unit, l->unit);
    }
    l->length--;
    return 0;
}

int
arraylist_remove_last (arraylist_t * l, void * e) 
{
	if(l->length == 0)
        return 1;
    
    memcpy(l->elements+(l->length-1)*l->unit, e, l->unit);
    l->length --;
    return 0;
}

int
arraylist_get (arraylist_t * l, int pos, void * e)
{
	if(l->length <= pos)
        return 1;
    
    memcpy(e,l->elements+pos*l->unit,l->unit);
    return 0;
}

void
arraylist_sort (arraylist_t * l, int (* cmp_elements)(void * e1, void * e2))
{
	/*TODO*/

}

void
_arraylist_qsort (arraylist_t * l, int (* cmp_elements)(void * e1, void * e2), void * begin, void * end)
{
	if(begin > end - l->unit)
        return ;
    
    int unit = l->unit;
    void* t = malloc(sizeof(unit));

    //elements 시작점
    void * pivot = begin; 
    void * lbound = begin + unit; //첫번째 element 끝나는 지점
    void * rbound = end - unit; //마지막 element 시작지점

    //피벗보다 작은요소는 피벗 왼쪽에
    //피벗보다 큰요소는 피벗 오른쪽에 있어야함

    //lbound와 rbound가 교차하지 않을 동안 반복합니다.
    while (lbound <= rbound) {
        //ex) 첫번째 단어랑 두번째 단어 비교해서 1나오면 첫번째 숫자가 더 크므로 out
         // 왼쪽 경계가 피벗보다 큰 요소를 찾을 때까지 이동
        while(lbound <= end - unit && cmp_elements(lbound, pivot) <= 0)
            lbound += unit;
         // 오른쪽 경계가 피벗보다 작은 요소를 찾을 때까지 이동
        while(begin < rbound && cmp_elements(pivot,rbound) < 0)
            rbound -= unit;
        
        // 찾으면 rbound pivot lbound순으로 바꿔야됨

        //lbound와 rbound가 교차하지 않았다면 두 요소를 교체합니다.
        if(lbound <= rbound){
            memcpy(t, lbound, unit) ;
            memcpy(lbound, rbound, unit) ;
            memcpy(rbound, t, unit) ;
            //업데이트
            lbound += unit ;
            rbound -= unit ;
        }
    }
    //교차하면 : rbound는 피벗보다 작은 요소중에 가장 큰요소의 시작주소를 가르킴. 원래 rbound는 피벗보다 큰요소의 주소를 가르켜야되니까 둘이 바꿔줌
    memcpy(t, rbound, unit) ;
	memcpy(rbound, pivot, unit) ;
	memcpy(pivot, t, unit) ;
	free(t) ;


    if (rbound != end - unit) {
		_arraylist_qsort(l, cmp_elements, begin, rbound + unit) ;
		_arraylist_qsort(l, cmp_elements, rbound + unit, end) ;
	}
	else {
		_arraylist_qsort(l, cmp_elements, begin, rbound) ;
	}
}

void
arraylist_qsort (arraylist_t * l, int (* cmp_elements)(void * e1, void * e2))
{
	_arraylist_qsort(1,cmp_elements,l->elements,l->elements+l->length*l->unit);
}
