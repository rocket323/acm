#include <iostream>
#include <cmath>
using namespace std;

long long N, A[1001], ans;

int main(){
	long long i,j,k;
	scanf("%I64d", &N);
	for(i=1; i<=N; ++i){
		scanf("%I64d", &A[i]);
	}
	ans=0;
	for(i=1; i<=N; ++i){
		for(j=1; j<=N; ++j)
			ans+=abs(A[i]-A[j]);
	}
	printf("%I64d\n", ans);
	return 0;
}
