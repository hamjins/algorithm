#include <iostream>
#include <cstdio>
#include <time.h>

int floor(int*, int, int, int);
int ceiling(int*, int, int, int);

int main() {
	int N, K;
	scanf("%d", &N);
	int* data = new int[N];
	for (int i = 0; i < N; i++) scanf("%d", &data[i]);
	scanf("%d", &K);
	clock_t st, et;
	st = clock();
	printf("%d \n", floor(data, 0, N - 1, K));
	printf("%d \n", ceiling(data, 0, N - 1, K));
	et = clock();
}

int floor(int* arr, int src, int dst, int K) {
	//mid is always on the smaller side. 
	int mid = (src + dst) / 2;
	if (arr[mid] == K) return arr[mid];
	if (src < dst) {
		//Let 's say we find 6 when there are 4 5 8 10.
		//Because it is greater than 5, 8 10 remain.
		//8 10 are all greater than 6. arr[mid] = 8 return
		if (arr[mid] > K) return floor(arr, src, mid, K);
		//다음 탐색 때 큰 쪽에 mid를 포함시키면 2개인 상황에서 mid가 변하질 않는다 
		else return floor(arr, mid+1, dst, K);
		//K가 arr[mid]보다 작으면 , =>arr[mid]가 ceiling 일수도있으니 mid 포함
		//K 가 arr[mid]보다 크면, =>arr[mid]가 ceiling 일 가능성은 없으니 포함 X 
	}
	if (src == dst) {
		//하나 남은 값이 K 보다 크게 나왔을 때, 그 밑의 인덱스를 가져오기 
		if (arr[mid] > K) {
			if (mid > 0) return arr[mid - 1];
		}
		else return arr[mid];
	}
	return -1;
}

//*(&arr)은더블포인터에서 *안써도 될 때 사용
int ceiling(int* arr, int src, int dst, int K) {
	int mid = (src + dst) / 2;
	if (src < dst) {
		if (arr[mid] == K) return arr[mid];
		//return 꼭 붙여주기. 리터럴값을 stack에 계속 반환시켜 마지막에도 같은 값 나오도록 유도
		else if (arr[mid] < K) return ceiling(arr, mid+1, dst, K);
		else return ceiling(arr, src, mid, K);
	}
	if (src == dst) {
		//K값이 배열의 모든 값보다 클 때
		if (arr[mid] < K) return -1;
		else return arr[mid];
	}
} 