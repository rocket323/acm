#include <iostream>
using namespace std;

int N, ans, A[2001], S[2001];
int f[2001], f1[2001], f2[2001];

int Max(int a, int b){
	return (a>b)?a:b;
}

void process(){
	int i,j,k, cnt=1, p1=1, p2=1, ans=0;
	for(i=1; i<=N; i++) f2[i]=f1[i]=f[i]=A[i];
	for(k=2; k<=N; ++k){
		for(i=1; i<=N-k+1; ++i){
			j=i+k-1;
			f[i]=Max(f1[i+1]+A[i]+S[j]-S[i], f1[i]+A[j]+S[j-1]-S[i-1]);
		}
		for(i=1; i<=N; ++i)
			f1[i]=f[i];
	}
	
	printf("%d\n", f[1]);
}

int main(){
	scanf("%d", &N);
	S[0]=0;
	for(int i=1; i<=N; i++){
		scanf("%d", &A[i]);
		S[i]=S[i-1]+A[i];
	}
	process();
	return 0;
}
