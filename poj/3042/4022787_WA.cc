#include <iostream>
#include <cmath>
#include <algorithm>
#define MaxL 800000000
using namespace std;

int f[1001][1001], g[1001][1001], N, S, sum[1002];
int A[1001];

void init(){
	int i,j,k, pos;
	scanf("%d%d", &N, &S);
	for(i=1; i<=N; ++i) scanf("%d", &A[i]);
	sort(A+1, A+1+N);
	for(i=1; i<=N; ++i) f[i][i]=g[i][i]=(abs(S-A[i]))*N;
}

int Min(int a, int b){
	return (a<b)?a:b;
}


void process(){
	int i,j,k;
	for(k=2; k<=N; ++k){
		for(i=1; i<=N+1-k; ++i){
			j=i+k-1;
			f[i][j]=MaxL;
			f[i][j]=Min(f[i][j], f[i+1][j]+(A[i+1]-A[i])*(i+N-j));
			f[i][j]=Min(f[i][j], f[i][j-1]+(2*A[j]-A[j-1]-A[i])*(i-1+N+1-j));
			f[i][j]=Min(f[i][j], g[i+1][j]+(A[j]-A[i])*(i+N-j));
			f[i][j]=Min(f[i][j], g[i][j-1]+(A[j]-A[j-1]+A[j]-A[i])*(i-1+N+1-j));
			
			g[i][j]=MaxL;
			g[i][j]=Min(g[i][j], g[i+1][j]+(A[i+1]-A[i]+A[j]-A[i])*(i+N-j));
			g[i][j]=Min(g[i][j], g[i][j-1]+(A[j]-A[j-1])*(i-1+N+1-j));
			g[i][j]=Min(g[i][j], f[i+1][j]+(A[i+1]+A[j]-2*A[i])*(i+N-j));
			g[i][j]=Min(g[i][j], f[i][j-1]+(A[j]-A[i])*(i-1+N+1-j));
		}
	}
}

int main(){
//	freopen("ontherun.9.in", "r", stdin);
//	freopen("oo.out", "w", stdout);
	init();
	process();
//	while(1);
	return 0;
}
