#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

long long N, A[10001], ans;

int main(){
	long long i,j,k;
	scanf("%I64d", &N);
	for(i=1; i<=N; ++i){
		scanf("%I64d", &A[i]);
	}
	sort(A+1, A+1+N);
	int t=N-1;
	for(i=N; i>=1; --i){
		ans+=(t*A[i]);
		t-=2;
	}
	ans=2*ans;
	printf("%I64d\n", ans);
	return 0;
}
