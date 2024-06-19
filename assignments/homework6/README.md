# DataStructure_HomeWork6 #

### 설명 ###
이 프로젝트는 각 sort 알고리즘에 대한 프로세스 평균 시간을 구하는 프로젝트 입니다.

sort 알고리즘의 종류로는 insert, heap, quick, merge 이 있으며,

input data의 종류로는 data-25000,data-50000,data-100000,data-200000 이 있습니다.

쉘 스크립트를 돌리게 되면 각 데이터에 따라서 알고리즘별로 100번 씩 정렬 프로세스를 실행 한 다음 정렬된 결과 값은 output 폴더에 저장하고, 100개의 프로세스 평균 runtime을 계산하여 result.txt에 저장하게 됩니다. 

### 실행 방법 ###
gcc -o sort sort.c
chmod +x run_sort.sh
./run_sort

다음과 같이 실행하면, result.txt에서 실행되는 결과 값을 보실수 있습니다. 

### 주의 사항 ###
./run_sort 실행 후,
10만 데이터와 20만 데이터의 경우 insert process의 경우 한 프로세스당 2초에서 8초가 시간이 소요됩니다.