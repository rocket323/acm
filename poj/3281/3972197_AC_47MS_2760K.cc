#include <iostream>
#define MaxN 600
#define MaxL 10000000
using namespace std;

int pre[MaxN], G[MaxN][MaxN], idx[MaxN][MaxN], cnt[MaxN];
int N, D, F, S, T, lt[MaxN], Q[600], head, tail;

void addEdge(int a, int b, int w){
	cnt[a]++; cnt[b]++;
	G[a][b]=w;
	G[b][a]=0;
	idx[a][cnt[a]]=b;
	idx[b][cnt[b]]=a;
}

void buildGraph(){
	int i,j,k, p, a, b;
	memset(cnt, 0, sizeof cnt);
	memset(G, 0, sizeof G);
	scanf("%d%d%d", &N, &F, &D);
	
	S=0; T=2*N+D+F+1;
	for(i=1; i<=N; i++) addEdge(i, i+N, 1);
	for(i=2*N+1; i<=2*N+F; i++) addEdge(S, i, 1);
	for(i=2*N+F+1; i<=2*N+F+D; i++) addEdge(i, T, 1);
	
	for(i=1; i<=N; i++){
		scanf("%d%d", &a, &b);
		for(j=1; j<=a; j++){
			scanf("%d", &p);
			addEdge(2*N+p, i, 1);
		}
		for(j=1; j<=b; j++){
			scanf("%d", &p);
			addEdge(i+N, 2*N+F+p, 1);
		}
	}
}

bool bfs( ){
	int i,j,k, p;
	head=tail=1;
	Q[1]=S;
	memset(lt, 0, sizeof lt);
	lt[S]=1;
	while(head<=tail){
		k=Q[head];
		for(i=1; i<=cnt[k]; ++i){
			p=idx[k][i];
	//	for(p=S; p<=T; p++){
			if(lt[p]==0&&G[k][p]>0){
				lt[p]=1;
				Q[++tail]=p;
				pre[p]=k;
			}
		}
		head++;
	}
	return lt[T];
}

int MaxFlow(){
	int i,j,k, Min, res=0;
	while(bfs()){
		k=T;
		Min=MaxL;
		while(k!=S){
			if(Min>G[pre[k]][k]) Min=G[pre[k]][k];
			k=pre[k];
		}
		res+=Min;
		k=T;
		while(k!=S){
			G[pre[k]][k]-=Min; G[k][pre[k]]+=Min;
			k=pre[k];
		}
	}
	return res;
}

int main(){
	int i,j,k;
//	freopen("dining.6.in", "r", stdin);
//	freopen("oo.out", "w", stdout);
	buildGraph();
	printf("%d\n", MaxFlow());
//	while(1);
	return 0;
}
	
