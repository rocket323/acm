#include <iostream>
using namespace std;

int f[10001], N, M, K;

int main(){
	int i,j,k;
	scanf("%d%d%d", &N, &K, &M);
	while(N!=0){
		f[1]=0;
		for(i=2; i<=N; i++)
			f[i]=(f[i-1]+K)%i;
		f[N]=(f[N]+M)%N;
		
		f[N]-=K;
		while(f[N]<0) f[N]+=N;
		printf("%d\n", f[N]+1);
		scanf("%d%d%d", &N, &K, &M);
	}
//	system("pause");
	return 0;
}
