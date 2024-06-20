#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * merge(int * a, int n_a, int* b, int n_b){
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
            top_b ++;
        }
    }
    return c;
}

void sort (int * a, int left, int right, int level){
    if(left >= right)
        return;

    int pivot = left;
    int l = left + 1;
    int r = right;

    while(l < r){
        while(l <= right && a[l] < a[pivot])
            l++;
        while(left + 1 <= r && a[pivot] < a[r])
            r--;

        if(l < r){
            int tmp = a[l];
            a[l] = a[r];
            a[r] = tmp;
            l++;
            r--;
        }
    }

    int tmp = a[pivot];
    a[pivot] = a[r];
    a[r] = tmp;

    sort(a, left, r - 1, level + 1);
    sort(a, r + 1, right, level + 1);

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

	sort(data, 0, n_data - 1, 0) ;

	for (int i = 0 ; i < n_data ; i++) {
		printf("%3d ", data[i]) ;
		if (i % 8 == 7) {
			printf("\n") ;
		}
	}

	return EXIT_SUCCESS ;
}
