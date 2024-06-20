#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>


void heapify(int * a, int n, int i){
    int largest = i;
	int left = i * 2 + 1;
	int right = i * 2 + 2;

	if(left < n && a[left] > a[largest])
		largest = left;
	if(right < n && a[right] > a[largest])
		largest = right;
	
	if(largest != i){
		int tmp;
		tmp = a[largest];
		a[largest] = a[i];
		a[i] = tmp;

		heapify(a, n, largest);
	}
}


void heap_sort(int * a, int n_a){
	for(int i = n_a / 2 - 1; i >= 0; i--){
		heapify(a, n_a, i);
	}

	for(int i = n_a - 1; i >= 0; i--){
		int tmp;
		tmp = a[i];
		a[i] = a[0];
		a[0] = tmp;

		heapify(a, i, 0);
	}
}

int* merge(int * a, int n_a, int* b, int n_b){	
	int n_c = n_a + n_b;
	int * c = malloc(n_c * sizeof(int));

	int top_a = 0;
	int top_b = 0;
	for(int i = 0; i < n_c; i++){
		if(top_b == n_b || (top_a < n_a && a[top_a] < b[top_b])){
			c[i] = a[top_a];
			top_a ++;
		}
		else{
			c[i] = b[top_b];
			top_b++;
		}
	}

	return c;
}

void merge_sort(int* a, int n_a){
	if(n_a == 0 || n_a == 1)
		return;

	int * a1;
	int n_a1;
	int * a2;
	int n_a2;
	a1 = a;
	n_a1 = n_a / 2;
	a2 = a + n_a1;
	n_a2 = n_a - n_a1;

	merge_sort(a1, n_a1);
	merge_sort(a2, n_a2);

	//when all spliting is done
	int * a_sorted;
	a_sorted = merge(a1, n_a1, a2, n_a2);

	memcpy(a, a_sorted, n_a*sizeof(int));
	free(a_sorted);
}

void quick_sort(int* a, int begin, int end){
	if(begin >= end)
		return;
	
	int p = begin;
	int l = begin + 1;
	int r = end;

	while(l < r){
		while(l < end && a[l] < a[p])
			l++;
		while(begin < r && a[p] < a[r])
			r--;
		
		if(l < r){
			int tmp;
			tmp = a[l];
			a[l] = a[r];
			a[r] = tmp;

			l++;
			r--;
		}
	}

	int tmp;
	tmp = a[p];
	a[p] = a[r];
	a[r] = tmp;

	quick_sort(a, begin, r - 1);
	quick_sort(a, r + 1, end);
}

int main ()
{
	int data [] = {
		26,  8, 81, 95,  7,  37,  63,  83,
		97, 98, 43, 76, 14,  81,  47,   5,
		 3,  8, 56, 59, 60, 100,  74,  91,
		97,  3, 98, 80, 82,  72,  84, 100,
		62, 35, 18, 54,  0,   8,   7,  15,
		57, 28,  2, 20, 46,  17,  75,  28,
		85, 55, 67,  9, 23,  38,  62,  59,
		90, 43, 98, 92, 81,  26,  21,  75
	} ;

	
	int n_data = sizeof(data) / sizeof(int) ;

	heap_sort(data, n_data) ;
	//quick_sort(data, 0, n_data - 1);
	//merge_sort(data, n_data);

	for (int i = 0 ; i < n_data ; i++) {
		printf("%3d ", data[i]) ;
		if (i % 8 == 7) {
			printf("\n") ;
		}
	}

	return EXIT_SUCCESS ;
}