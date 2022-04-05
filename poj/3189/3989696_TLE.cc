#include <iostream>
#define MaxN 1100
#define MaxL 10000000
using namespace std;

int N, B, M, pri[1001][21], C[21], S, T;
int G[MaxN][MaxN], pre[MaxN], cnt[MaxN], idx[MaxN][MaxN];
int Q[MaxN];
bool lt[MaxN];

void init(){
	int i,j,k;
	scanf("%d%d", &N, &B);
	for(i=1; i<=N; ++i){
		for(j=1; j<=B; ++j){
			scanf("%d", &k);
			pri[i][k]=j;
		}
	}
	for(i=1; i<=B; ++i) scanf("%d", &C[i]);
}

void addEdge(int a, int b, int c){
	cnt[a]++;
	G[a][b]=c;
	idx[a][cnt[a]]=b;
}

bool bfs(){
	int i,j,k,p, head, tail;
	memset(lt, 0, sizeof lt);
	Q[head=tail=1]=S; lt[S]=1;
	while(head<=tail){
		k=Q[head];
		for(i=1; i<=cnt[k]; ++i){
			p=idx[k][i];
			if(!lt[p]&&G[k][p]>0){
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
	int i,j,k, Min, ans=0;
	while(bfs()){
		k=T; Min=MaxL;
		while(k!=S){
			if(Min>G[pre[k]][k]) Min=G[pre[k]][k];
			k=pre[k];
		}
		ans+=Min;
		k=T;
		while(k!=S){
			G[pre[k]][k]-=Min;
			G[k][pre[k]]+=Min;
			k=pre[k];
		}
	}
	return ans;
}

int check(int low, int high){
	int i,j,k;
	S=0; T=N+B+1;
	memset(cnt, 0, sizeof cnt);
	memset(G, 0, sizeof G);
	memset(pre, 0, sizeof pre);
	for(i=1; i<=N; ++i){
		addEdge(S, i, 1);
		addEdge(i, S, 0);
	}
	for(i=1; i<=N; ++i)
		for(j=1; j<=B; ++j)
			if(low<=pri[i][j]&&pri[i][j]<=high){
				addEdge(i, j+N, 1);
				addEdge(j+N, i, 0);
			}
	for(j=N+1; j<=N+B; ++j){
		addEdge(j, T, C[j-N]);
		addEdge(T, j, 0);
	}
//	return MaxFlow();
	if(MaxFlow()==N) return true;
	else return false;
}

void process(){
	int i,j,k, low=1, high=1, len=MaxL;
	while(low<=high&&high<=B){
		if(check(low, high)){
			if(high-low+1<len) len=high-low+1;
			low++;
		}
		else high++;
	}
	printf("%d\n", len);	
}

int main(){
	int i,j,k;
//	freopen("3189.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
