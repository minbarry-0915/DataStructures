#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

int 
string_cmp (void *e1, void *e2)
{
	char *s1 = *((char **)e1) ;
	char *s2 = *((char **)e2);
	return strcmp(s1, s2) ;
}

int 
main ()
{
	char * inputs[7] = {"necessary", "correct", "absent", "type", "because", "further", 0x0} ;
	int i ;

	heap_t * h = heap_create(6, sizeof(char *), string_cmp) ;
	
	printf("Task 1: Modify heap_push, heap_pop\n");
	for (i = 0 ; inputs[i] != 0x0 ; i++) {
		heap_push(h, &(inputs[i])) ;
	}

	//Task 1: revise function heap_push such that  it doubles the capacity when the heap becomes full
	char * input8 = "incorrect";
	heap_push(h, &(input8));
	
	//Task1: revise function heap_pop such that it halves the capacity when the number of remaining elements becomes less than the quarter of the capacity

	while (heap_size(h) > 0) {
		char * s = 0x0 ;
		heap_pop(h, &s) ;
		printf("%s\n", s) ;
	}
	printf("\n");

	// Task 2. Implement heap_remove
	//this function removes an element from heap that i sequal to the data given as buf.
	//two elements are considered to be equal if the cmp function returns 0 with the two elements
	//revise the main function to demonstrate this function

	printf("Task 2: Implement heap_remove\n");
	for (i = 0 ; inputs[i] != 0x0 ; i++) {
		heap_push(h, &(inputs[i])) ;
	}

	char* temp = "absent";
	printf("Target: %s\n\n", temp);
	heap_remove(h, &temp);
	while (heap_size(h) > 0) {
		char * s = 0x0 ;
		heap_pop(h, &s) ;
		printf("%s\n", s) ;
	}

	return 0 ;
}
