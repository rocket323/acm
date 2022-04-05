#include <iostream>
#define MaxN 1001
#define MaxL 10000001
using namespace std;

long long N, M, G[MaxN][MaxN], lowcost[MaxN];
long long vis[MaxN];

void init(){
	long long i,j,k, a, b, c;
	scanf("%I64d%I64d", &N, &M);
	for(i=1; i<=N; ++i)
		for(j=1; j<=N; ++j)
			G[i][j]=MaxL;
	for(i=1; i<=M; ++i){
		scanf("%I64d%I64d%I64d", &a, &b, &c);
		if(MaxL-c<G[a][b])
			G[a][b]=G[b][a]=MaxL-c;
	}
}

void process(){
	long long i,j,k, Min, res=0;
	for(i=2; i<=N; ++i){
		lowcost[i]=G[i][1];
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
		if(Min==MaxL){
			cout<<-1<<endl;
			return;
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
//	freopen("cowtract.4.in", "r", stdin);
//	freopen("oo.out", "w", stdout);
	init();
	process();
//	while(1);
	return 0;
}
