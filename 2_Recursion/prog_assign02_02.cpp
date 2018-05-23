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
		//���� Ž�� �� ū �ʿ� mid�� ���Խ�Ű�� 2���� ��Ȳ���� mid�� ������ �ʴ´� 
		else return floor(arr, mid+1, dst, K);
		//K�� arr[mid]���� ������ , =>arr[mid]�� ceiling �ϼ��������� mid ����
		//K �� arr[mid]���� ũ��, =>arr[mid]�� ceiling �� ���ɼ��� ������ ���� X 
	}
	if (src == dst) {
		//�ϳ� ���� ���� K ���� ũ�� ������ ��, �� ���� �ε����� �������� 
		if (arr[mid] > K) {
			if (mid > 0) return arr[mid - 1];
		}
		else return arr[mid];
	}
	return -1;
}

//*(&arr)�����������Ϳ��� *�Ƚᵵ �� �� ���
int ceiling(int* arr, int src, int dst, int K) {
	int mid = (src + dst) / 2;
	if (src < dst) {
		if (arr[mid] == K) return arr[mid];
		//return �� �ٿ��ֱ�. ���ͷ����� stack�� ��� ��ȯ���� ���������� ���� �� �������� ����
		else if (arr[mid] < K) return ceiling(arr, mid+1, dst, K);
		else return ceiling(arr, src, mid, K);
	}
	if (src == dst) {
		//K���� �迭�� ��� ������ Ŭ ��
		if (arr[mid] < K) return -1;
		else return arr[mid];
	}
} 