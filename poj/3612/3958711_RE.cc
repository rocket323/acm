#include <iostream>
#include <cmath>
#define MaxN 100010
#define MaxL 10000000
using namespace std;

int N, C, A[MaxN], Max, B[MaxN];
int f[200][201], l[200][201], h[200][201];

void init(){
	int i,j,k;
	scanf("%d%d", &N, &C);
	Max=0;
	for(i=1; i<=N; ++i){
		scanf("%d", &A[i]);
		if(A[i]>Max) Max=A[i];
	}
}

int Min(int a, int b){
	return (a<b)?a:b;
}

void process(){
	int i,j,k, ans=MaxL;
	
	for(i=0; i<=N; ++i)
		for(j=0; j<=100; ++j){
			h[i][j]=MaxL;
			l[i][j]=MaxL;
			f[i][j]=MaxL;
		}
	
	
	for(i=A[1]; i<=100; i++) f[1][i]=(i-A[1])*(i-A[1]);
	
	l[1][A[1]]=f[1][A[1]]-C*A[1];
	for(i=A[1]+1; i<=100; i++)
		l[1][i]=Min(f[1][i]-C*i, l[1][i-1]);
		
	h[1][100]=f[1][100]+C*100;
	for(i=99; i>=1; i--)
		h[1][i]=Min(f[1][i]+C*i, h[1][i+1]);
		
		
		
	for(i=2; i<=N; ++i){
		for(j=A[i]; j<=100; ++j){
			f[i][j]=Min(l[i-1][j]+C*j, h[i-1][j]-C*j) + (j-A[i])*(j-A[i]);
		}
		
		l[i][A[i]]=f[i][A[i]]-C*A[i];
		for(j=A[i]+1; j<=100; ++j)
			l[i][j]=Min(f[i][j]-C*j, l[i][j-1]);
		
		h[i][100]=f[i][100]+C*100;
		for(j=99; j>=1; --j)
			h[i][j]=Min(f[i][j]+C*j, h[i][j+1]);
	}
	
	for(i=A[N]; i<=100; ++i)
		if(f[N][i]<ans)
			ans=f[N][i];
	cout<<ans<<endl;
//	cout<<f[4][3]<<endl;
}

int main(){
	int i,j,k;
//	freopen("3612.in", "r", stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
