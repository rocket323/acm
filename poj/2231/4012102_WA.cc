#include <iostream>
#include <cmath>
using namespace std;

int N, A[1001], ans;

int main(){
	int i,j,k;
	scanf("%d", &N);
	for(i=1; i<=N; ++i){
		scanf("%d", &A[i]);
	}
	ans=0;
	for(i=1; i<=N; ++i){
		for(j=1; j<=N; ++j)
			ans+=abs(A[i]-A[j]);
	}
	printf("%d\n", ans);
	return 0;
}
