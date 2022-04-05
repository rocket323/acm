#include <iostream>
#define MaxL 10000000
using namespace std;

int N, M, A[501], B[501], f[501][501];
int p1[501][501], p2[501][501];
int st[501], top;
int loc[501][501];

void init()
{
	int i,j,k;
	for(i=1; i<=N; ++i) scanf("%d", &A[i]);
	scanf("%d", &M);
	for(i=1; i<=M; ++i) scanf("%d", &B[i]);
	for(i=1; i<=N; ++i){
		for(j=1; j<=M; ++j){
			loc[i][j]=0;
			for(k=1; k<=j; ++k)
				if(A[i]==B[k])
					loc[i][j]=k;
		}
	}
	memset(p1, 0, sizeof p1);
	memset(p2, 0, sizeof p2);
}

void out(int s1, int s2){
	if(s1==0) return;
	out(p1[s1][s2], p2[s1][s2]);
	st[++top]=A[s1];
}

void process(){
	int i,j,k, p, q;
	int s1=0, s2=0, Max=0;
	memset(f, 0, sizeof f);
	for(i=1; i<=M; ++i)
		if(A[1]==B[i]) f[1][i]=1;
	for(i=1; i<=N; ++i)
		if(A[i]==B[1]) f[i][1]=1;
	for(i=2; i<=N; ++i)
		for(j=2; j<=M; ++j){
			f[i][j]=0;
			if(A[i]==B[j]){
				for(p=1; p<i; ++p){
					if(A[p]>=A[i]) continue;
					q=loc[p][j-1];
					if(f[p][q]+1>f[i][j]){
						f[i][j]=f[p][q]+1;
						p1[i][j]=p; p2[i][j]=q;
					}
				}
			}
			if(f[i][j]>Max){
				Max=f[i][j];
				s1=i; s2=j;
			}
		}
	printf("%d\n", Max);
	top=0;
	out(s1, s2);
	if(Max==0) return;
	for(i=1; i<top; ++i) printf("%d ", st[i]);
	printf("%d\n", st[top]);
}

int main()
{
//	freopen("2127.in", "r", stdin);
	while(scanf("%d", &N)!=EOF)
	{
		init();
		process();
	}
//	while(1);
	return 0;
}
