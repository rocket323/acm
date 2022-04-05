#include <iostream>
#define MaxL 10000000
using namespace std;

int N, M, f[303][303];
int A[303], B[303];
int S1[303], S2[303];

void init(){
	scanf("%d%d", &M, &N);
	
	S1[0]=S2[0]=0;
	for(int i=1; i<=N; i++){
		scanf("%d%d", &A[i], &B[i]);
		S1[i]=S1[i-1]+A[i];
		S2[i]=S2[i-1]+B[i];
	}
}

void process(){
	int i,j,k, ans=MaxL;
	
	for(i=1; i<=N; i++)
		for(j=1; j<=N; j++)
			f[i][j]=MaxL;
	
	for(j=1; j<=N; j++)
		if(S1[j]<=M)
			f[1][j] = 1;
	
	
	for(i=2; i<=N; i++)
		for(j=i; j<=N; j++){
			f[i][j]=MaxL;
			for(k=1; k<i; k++){
				if(S2[i-1]-S2[k-1] + S1[j]-S1[i-1]>M){
					if(f[i][j]>f[k][i-1]+2&&(S2[i-1]-S2[k-1]<=M)&&(S1[j]-S1[i-1]<=M))
						f[i][j]=f[k][i-1]+2;
				}
				else 
				if(f[i][j] > f[k][i-1] + 1&&(S2[j]-S2[i-1]<=M))
					f[i][j] = f[k][i-1] + 1;
			}
			if(j==N&&f[i][j]<ans&&(S2[j]-S2[i-1]<=M)) ans=f[i][j];
		}
	printf("%d\n", ans+2);
}

int main(){
	int i,j,k;
	init();
	process();
	return 0;
}