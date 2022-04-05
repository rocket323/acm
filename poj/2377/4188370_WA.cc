#include <iostream>
#define MaxN 1001
#define MaxL 1000001
using namespace std;

int N, M, G[MaxN][MaxN], lowcost[MaxN];
int vis[MaxN];

void init(){
	int i,j,k, a, b, c;
	scanf("%d%d", &N, &M);
	memset(G, -1, sizeof G);
	for(i=1; i<=M; ++i){
		scanf("%d%d%d", &a, &b, &c);
		G[a][b]=G[b][a]=MaxL-c;
	}
}

void process(){
	int i,j,k, Min, res=0;
	for(i=2; i<=N; ++i){
		lowcost[i]=G[i][1];
		if(lowcost[i]==-1) lowcost[i]=MaxL;
	}
	memset(vis, 0, sizeof vis);
	vis[1]=1;
	for(i=1; i<N; ++i){
		Min=MaxL;
		for(j=2; j<=N; ++j){
			if(lowcost[j]<Min&&!vis[j]){
				Min=lowcost[j];
				k=j;
			}
		}
		res+=Min; vis[k]=1;
		for(j=2; j<=N; ++j){
			if(lowcost[j]>G[k][j])
				lowcost[j]=G[k][j];
		}
	}
	cout<<(N-1)*MaxL-res<<endl;
}

int main(){
//	freopen("2377.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
