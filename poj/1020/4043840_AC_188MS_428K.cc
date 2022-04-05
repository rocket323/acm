#include <iostream>
#include <algorithm>
using namespace std;

int S, N, A[19], sum;
bool vis[19], G[100][100];
bool flag, check, Notpast[41][41][11];
int ri, rj;

bool cmp(int a, int b){
	return (a>b);
}

void init(){
	int i,j,k;
	scanf("%d", &S);
	scanf("%d", &N);
	sum=0;
	for(i=1; i<=N; ++i){
		scanf("%d", &A[i]);
		sum+=(A[i]*A[i]);
	}
	sort(A+1, A+1+N);
	memset(vis, 0, sizeof vis);
	memset(G, 0, sizeof G);
	memset(Notpast, 0, sizeof Notpast);
}

bool can(int ri , int rj, int size){
	int i,j,k;
	if(ri+size-1>S) return false;
	if(rj+size-1>S) return false;
	for(i=ri; i<ri+size; ++i)
		for(j=rj; j<rj+size; ++j)
			if(G[i][j]) return false;
	return true;
}

inline void find(int lr, int lc){
	int i,j;
	for(j=lc; j<=S; ++j)
		if(G[lr][j]==0){
			check=1;
			ri=lr; rj=j;
			return;
		}
	for(i=lr+1; i<=S; ++i)
		for(j=1; j<=S; ++j)
			if(G[i][j]==0){
				check=1;
				ri=i; rj=j;
				return ;
			}
}

void dfs(int now, int lr, int lc){
 	if(flag) return;
	if(now==N+1){
		flag=1;
		return;
	}
	check=0;
	int i, j, k;
	find(lr,  lc);
	if(!check) return;
	int si=ri, sj=rj, cannt=0;
	for(i=1; i<=N; ++i){
		if(vis[i]) continue;
		if(cannt==A[i]) continue;
		if(can(si, sj, A[i])){
			vis[i]=1;
			int ii, jj;
			for(ii=si; ii<si+A[i]; ++ii)
				for(jj=sj; jj<sj+A[i]; ++jj)
					G[ii][jj]=1;
			
			dfs(now+1, 1, 1);
			
			if(!flag) cannt=A[i];
			vis[i]=0;
			for(ii=si; ii<si+A[i]; ++ii)
				for(jj=sj; jj<sj+A[i]; ++jj)
					G[ii][jj]=0;
		}
		else break;
	}
}

void process(){
	int i,j,k;
	if(S*S!=sum){
		printf("HUTUTU!\n");
		return;
	}
	flag=0;
	dfs(1, 1, 1);
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
//	while(1);
	return 0;
}
