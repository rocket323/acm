#include <iostream>
using namespace std;

int S, N, A[19];
bool vis[19], G[100][100];
bool flag;

void init(){
	int i,j,k;
	scanf("%d", &S);
	scanf("%d", &N);
	for(i=1; i<=N; ++i) scanf("%d", &A[i]);
	memset(vis, 0, sizeof vis);
	memset(G, 0, sizeof G);
}

bool can(int ri , int rj, int size){
	int i,j,k;
	for(i=ri; i<ri+size; ++i)
		for(j=rj; j<rj+size; ++j)
			if(G[i][j]) return false;
	return true;
}

void dfs(int now){
	if(flag) return;
	if(now==N+1){
		flag=1;
		return;
	}
	bool check=0;
	int ri, rj, i, j, k;
	for(i=1; i<=S; ++i)
		for(j=1; j<=S; ++j)
			if(G[i][j]==0){
				check=1;
				ri=i; rj=j;
				break;
			}
	for(i=1; i<=N; ++i){
		if(vis[i]) continue;
		if(can(ri, rj, A[i])){
			vis[i]=1;
			int ii, jj;
			for(ii=ri; ii<ri+A[i]; ++ii)
				for(jj=rj; jj<rj+A[i]; ++jj)
					G[ii][jj]=1;

			dfs(now+1);

			vis[i]=0;
			for(ii=ri; ii<ri+A[i]; ++ii)
				for(jj=rj; jj<rj+A[i]; ++jj)
					G[ii][jj]=0;
		}
	}
}

void process(){
	int i,j,k;
	if(S>40){
		printf("HUTUTU!\n");
		return;
	}
	flag=0;
	dfs(1);
	if(flag) printf("KHOOOOB!\n");
	else printf("HUTUTU!\n");
}

int main(){
	int i, T;
//	freopen("1020.in", "r", stdin);
	scanf("%d", &T);
	for(i=1; i<=T; ++i){
		init();
		process();
	}
	return 0;
}