#include <iostream>
#define MaxN 10010
using namespace std;

struct Edge{
	int idx;
	Edge *next;
};

Edge adj[MaxN], memo[MaxN];

int N, M, L[MaxN], P[MaxN][16], mset, D[MaxN];

void addEdge(int a, int b){
	Edge *ptr=&memo[mset++];
	ptr->idx=b;
	ptr->next=adj[a].next;
	adj[a].next=ptr;
}

void dfs(int now, int lev){
	L[now]=lev;
	
	Edge* ptr=adj[now].next;
	while(ptr){
		int k=ptr->idx;
		if(L[k]==-1) dfs(k, lev+1);
		ptr=ptr->next;
	}
}

void LCA_ready(){
	int i,j,k;
	memset(P, -1, sizeof P);
	for(i=1; i<=N; ++i) P[i][0]=D[i];
	for(j=1; (1<<j)<=N; ++j)
		for(i=1; i<=N; ++i)
			if(P[i][j-1]!=-1)
				P[i][j]=P[P[i][j-1]][j-1];
}

int LCA(int a, int b){
	int i,j,k, log, tmp;
	if(L[a]<L[b]){ tmp=a; a=b; b=tmp; }
	for(log=1; (1<<log)<=L[a]; ++log);
	--log;
	for(i=log; i>=0; --i)
		if(L[a]-(1<<i)>=L[b])
			a=P[a][i];
	
	if(a==b) return a;
	
	for(i=log; i>=0; --i)
		if(P[a][i]!=-1&&P[a][i]!=P[b][i]){
			a=P[a][i]; b=P[b][i];
		}
	return D[a];
}

void init(){
	int i,j,k, a, b;
	scanf("%d", &N);
	
	for(i=1; i<=N; ++i) adj[i].next=NULL;
	mset=0;
	memset(L, -1, sizeof L);
	
	memset(D, -1, sizeof D);
	for(i=1; i<N; ++i){
		scanf("%d%d", &a, &b);
		addEdge(a, b);
		D[b]=a;
	}
	for(i=1; i<=N; ++i)
		if(D[i]==-1)
			dfs(i, 0);
	LCA_ready();
}

void process(){
	int i,j,k, a, b;
	scanf("%d%d", &a, &b);
	printf("%d\n", LCA(a, b));
}

int main(){
	int T;
//	freopen("1330.in", "r", stdin);
	scanf("%d", &T);
	while(T--){
		init();
		process();
	}
//	while(1);
	return 0;
}
