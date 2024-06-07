#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"

typedef struct {
	int key ;
	char data[64] ;
} entry ;

//키값만 비교
int
_cmp (void * p1, void * p2)
{
	entry* s1 = (entry*)p1;
	entry* s2 = (entry*)p2;
	return s1->key - s2->key;
}

void
_print (void * p)
{
	entry*s = (entry*)p;
	printf("[%d, %s]", s->key,s->data);
}

int
main ()
{
	int i ;

	entry d[10] = {{5, "Hello"}, {2, "Problem"}, {8, "Book"}, {9, "University"}, {4, "Reason"},
		{1, "Intelligence"}, {7, "Brain"}, {6, "Beginning"}, {3, "List"}, {10, "Market"}} ;

	bst_t * t = bst_create(sizeof(entry), _cmp) ;

	for (i = 0 ; i < 10 ; i++) {
		bst_insert(t, &(d[i])) ;
	}	
	bst_print(t, _print) ;

	entry query ;
	query.key = 9 ;

	if (bst_search(t, &query)) {
		printf("%s\n", query.data) ;
	}
	else {
		printf("no such element exists.\n") ;
	}

	
	for (i = 0 ; i < 11 ; i++) {
		bst_remove(t, &i) ;
		bst_print(t, _print) ;
	}
	
	bst_free(t) ;

	return EXIT_SUCCESS ;
}
