#include <iostream>
#define MaxN 1001000
using namespace std;

int A[MaxN], f1[MaxN][20], f2[MaxN][20];
int res[MaxN], res2[MaxN], N, M;

void init(){
	int i,j,k, t;
	scanf("%d%d", &N, &M);
	for(i=1; i<=N; ++i) scanf("%d", &A[i]);
	for(i=1; i<=N; ++i){
		f1[i][0]=i; f2[i][0]=i;
	}
	for(j=1; (1<<j)<=N; ++j){
		for(i=1; i+(1<<j)-1<=N; ++i){
			k=i+(1<<(j-1));
			if(A[f1[i][j-1]]<A[f1[k][j-1]]) f1[i][j]=f1[i][j-1];
			else f1[i][j]=f1[k][j-1];
			if(A[f2[i][j-1]]>A[f2[k][j-1]]) f2[i][j]=f2[i][j-1];
			else f2[i][j]=f2[k][j-1];
		}
	}
}

int Min(int a, int b){
	return (a<b)?a:b;
}

int Max(int a, int b){
	return (a>b)?a:b;
}

int query(int a, int b){
	int l, log=0;
	while((1<<log)<=(b-a+1)) ++log;
	log--;
	int k=b-(1<<log)+1;
	return Min(A[f1[a][log]], A[f1[k][log]]);
}

int query2(int a, int b){
	int l, log=0;
	while((1<<log)<=(b-a+1)) ++log;
	log--;
	int k=b-(1<<log)+1;
	return Max(A[f2[a][log]], A[f2[k][log]]);
}

void process(){
	int i,j,k;
	for(i=1; i+M-1<=N; ++i){
		res[i]=query(i, i+M-1);
		res2[i]=query2(i, i+M-1);
	}
	for(i=1; i<N+1-M; ++i) printf("%d ", res[i]);
	printf("%d\n", res[N+1-M]);
	for(i=1; i<N+1-M; ++i) printf("%d ", res2[i]);
	printf("%d\n", res2[N+1-M]);
}

int main(){
//	freopen("2823.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
