#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int T, N, A[50001];

bool cmp(int a, int b){
	return abs(a)<abs(b);
}

void process(){
	int i,j,k,tim=0;
	sort(A, A+N, cmp);
	tim=abs(A[0]);

	for(i=1; i<N; ++i){
	tim+=(abs(A[i]-A[i-1]));
		if(tim>T) break;
	}
	printf("%d\n", i);
}

int main(){

	scanf("%d%d", &T, &N);
	for(int i=0; i<N; ++i) scanf("%d", &A[i]);
	process();
	return 0;
}