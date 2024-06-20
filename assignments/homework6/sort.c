#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

enum algo_opt {
	Insert, 
	Heap,
	Quick,
	Merge 
} ;

char * algo_opts[5] = {
	"insert",
	"heap",
	"quick",
	"merge",
	NULL } ;

int n_elements = 0 ;
double * elements ;

int algo = 0 ;

FILE * fin = NULL ;
FILE * fout = NULL ; 

void load_elements ()
{
	int i ;
	for (i = 0 ; i < n_elements ; i++) {
		int r ;
		r = fscanf(fin, "%lf", &(elements[i])) ;
		if (r != 1) {
			fprintf(stderr, "Error. Failed at reading input file: %d\n", r) ;
			exit(EXIT_FAILURE) ;
		}
	}
}

void store_result ()
{
	int i ;
	for (i = 0 ; i < n_elements ; i++) {
		int r ;
		r = fprintf(fout, "%lf\n", elements[i]) ;
		if (r <= 0) {
			fprintf(stderr, "Error. Failed at writing the result.\n") ;
			exit(EXIT_FAILURE) ;
		}
	}
}

void insertion_sort ()
{	
	/*TODO*/
	int i;	
	int j;
	double temp;
	for(i = 1; i < n_elements; i++){
		temp = elements[i];
		j = i - 1;

		while(j >= 0 && elements[j] > temp){
			elements[j+1] = elements[j];
			j = j - 1;
		}
		elements[j + 1] = temp;
	}

	
}
void swap(int a, int b){
	double temp = elements[a];
	elements[a] = elements[b];
	elements[b] = temp;
}


void heapify(int n, int i) { //n: element 갯수 i: 시작점
    int largest = i; // 루트 노드
    int left = 2 * i + 1; // 왼쪽 자식 노드
    int right = 2 * i + 2; // 오른쪽 자식 노드

    // 왼쪽 자식 노드가 루트보다 큰 경우
    if (left < n && elements[left] > elements[largest])
        largest = left;

    // 오른쪽 자식 노드가 현재 가장 큰 노드보다 큰 경우
    if (right < n && elements[right] > elements[largest])
        largest = right;

    // 가장 큰 노드가 루트가 아닌 경우
    if (largest != i) {
        swap(largest, i);

        // 힙 구조 조정
        heapify(n, largest);
    }
}

void heap_sort ()
{
	/*TODO*/
	//최대 힙 만들기 
	for (int i = n_elements / 2 - 1; i >= 0; i--)
        heapify(n_elements, i);

	//힙에 제일 큰 값 꺼내서 배열 마지막에 박고 힙크기 줄여서 재정렬
	for (int i = n_elements - 1; i >= 0 ; i--){
		swap(i, 0);
		heapify(i, 0);
	}

}

void _quick_sort (int begin, int end){
	if(begin >= end - 1)
		return;

	//피봇, 왼쪽, 오른쪽 설정
	int pivot = begin;
	int lbound = begin + 1;
	int rbound = end - 1;
	
	//교차하지 않을때 까지
	while(lbound <= rbound){
		//피봇보다 작은 수 찾음
		while(lbound < end && elements[lbound] <= elements[pivot])
			lbound ++;
		//피봇보다 큰수 찾음
		while(begin < rbound && elements[pivot] < elements[rbound])
			rbound --;
		//교차 안하면 둘의 위치 바꿈
		if(lbound <= rbound){
			swap(lbound,rbound);
			lbound ++;
			rbound --;
		}		
	}	
	//교차하면: 더이상 피봇기준으로 바꿀게 없을때
	// 피봇이랑 오른쪽 인덱스랑 바꿈
	swap(pivot,rbound);
	//오른쪽 인덱스번호가 배열의 끝이 아니면
	if(rbound != end){
		//정렬 계속 진행
		_quick_sort(begin, rbound);
		_quick_sort(rbound+1, end);
	}
}

void quick_sort ()
{
	/*TODO*/
	_quick_sort(0,n_elements);
}

double* merge (double* a, int n_a, double* b, int n_b){
	double* c = malloc((n_a + n_b) * sizeof(double));

	int n_c = n_a + n_b;

	int top_a = 0;
	int top_b = 0;

	for(int i = 0; i < n_c; i++){
		//b의 배열을 다썻거나 a배열을 다 안쓰고 a의 배열이 b의 배열 보다 작을때
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

void _merge_sort(double* a, int n_a){
	//0개이거나 1개이면 이미 정렬끝
	if(n_a == 0 || n_a == 1)
		return;

	double* a1;
	int n_a1;
	double* a2;
	int n_a2;

	a1 = a;
	n_a1 = n_a / 2;

	a2 = a + n_a1;
	n_a2 = n_a - n_a1;
	
	//재귀
	_merge_sort(a1, n_a1);
	_merge_sort(a2, n_a2);

	double * a_sorted;

	//재귀 끝나면 합치기
	a_sorted = merge(a1, n_a1, a2, n_a2);
	memcpy(a, a_sorted, n_a* sizeof(double));
	free(a_sorted);
}

void merge_sort ()
{
	/*TODO*/
	_merge_sort(elements, n_elements);
}

void sort ()
{
	switch (algo) {
		case Insert :
			insertion_sort() ;
			break ;

		case Heap:
			heap_sort() ;
			break ;

		case Quick: 
			quick_sort() ;
			break ;

		case Merge:
			merge_sort() ;
			break ;

		default:
			fprintf(stderr, "Error. Unkown algorithm option.\n") ;
			exit(EXIT_FAILURE) ;
			break ;
	}
}


int main (int argc, char ** argv)
{
	struct timeval ts_begin ;
	struct timeval ts_end ;

	int opt ;
	while ((opt = getopt(argc, argv, "n:i:o:s:")) != -1) {
		switch (opt) {

			case 'n': {
				n_elements = atoi(optarg) ;

				if (n_elements <= 0 || 40000000 < n_elements) {
					fprintf(stderr, "Error. \'n\' must be a positive integer no greater than 10^9.\n") ;
					exit(EXIT_FAILURE) ;
				}

				elements = calloc(n_elements, sizeof(double)) ;
				break ;
			}

			case 'i' : {
				fin = fopen(optarg, "r") ;

				if (fin == NULL) {
					fprintf(stderr, "Error. Fail to open %s\n", optarg) ;
					exit(EXIT_FAILURE) ;
				}
				break ;
			}

			case 'o' : {
				fout = fopen(optarg, "w") ;
				if (fout == NULL) {
					fprintf(stderr, "Error. Fail to open %s\n", optarg) ;
					exit(EXIT_FAILURE) ;
				}
				break ;
			}

			case 's' : {
				while (algo_opts[algo] && strcmp(algo_opts[algo], optarg) != 0) {
					algo++ ;
				}
				if (algo_opts[algo] == NULL) {
					fprintf(stderr, "Usage: -n <num elements> -i <input file> -o <output file> -s [insert|heap|quick|merge]") ;
					exit(EXIT_FAILURE) ;
				}
				break ;
			}

			default: {
				fprintf(stderr, "Usage: -n <num elements> -i <input file> -o <output file> -s [insert|heap|quick|merge]") ;
				exit(EXIT_FAILURE) ;
				break ;
			}
		}
	}

	load_elements() ;

	gettimeofday(&ts_begin, NULL) ;

	sort() ;

	gettimeofday(&ts_end, NULL) ;

	store_result() ;


	if (ts_begin.tv_usec < ts_end.tv_usec) {
		printf("%ld.%06ld\n", 	
			(long int) (ts_end.tv_sec - ts_begin.tv_sec), 
			(long int) (ts_end.tv_usec - ts_begin.tv_usec)) ;
	}
	else {
		printf("%ld.%06ld\n",
			(long int) (ts_end.tv_sec - ts_begin.tv_sec - 1),
			(long int) (ts_begin.tv_usec - ts_end.tv_usec)) ;
	}

	if (fin)
		fclose(fin) ;
	if (fout)
		fclose(fout) ;

	return EXIT_SUCCESS ;
}
