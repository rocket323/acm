#include <iostream>
#include <cmath>
#define MaxN 100010
#define MaxL 10000000
using namespace std;

int N, C, A[MaxN], Max, B[MaxN];
int f[101], f1[101], l[101], l1[101], h[101], h1[101];

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
			h1[j]=h[j]=MaxL;
			l1[j]=l[j]=MaxL;
			f1[j]=f[j]=MaxL;
		}
	
	
	for(i=A[1]; i<=100; i++) f[i]=f1[i]=(i-A[1])*(i-A[1]);
	
	l1[A[1]]=f1[A[1]]-C*A[1];
	for(i=A[1]+1; i<=100; i++)
		l1[i]=Min(f1[i]-C*i, l1[i-1]);
		
	h1[100]=f1[100]+C*100;
	for(i=99; i>=1; i--)
		h1[i]=Min(f1[i]+C*i, h1[i+1]);
		
		
		
	for(i=2; i<=N; ++i){
		
		for(j=0; j<=100; ++j) f[j]=MaxL;
		
		for(j=A[i]; j<=100; ++j){
			f[j]=Min(l1[j]+C*j, h1[j]-C*j) + (j-A[i])*(j-A[i]);
		}
		
		for(j=0; j<=100; ++j){
			l[j]=MaxL;
			h[j]=MaxL;
		}
		
		l[A[i]]=f[A[i]]-C*A[i];
		
		for(j=A[i]+1; j<=100; ++j)
			l[j]=Min(f[j]-C*j, l[j-1]);
		
		h[100]=f[100]+C*100;
		for(j=99; j>=1; --j)
			h[j]=Min(f[j]+C*j, h[j+1]);
		
		memcpy(f1, f, sizeof f);
		memcpy(l1, l, sizeof l);
		memcpy(h1, h, sizeof h);
	}
	
	for(i=A[N]; i<=100; ++i)
		if(f[i]<ans)
			ans=f[i];
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
