#include <iostream>
#define MaxN 50001
using namespace std;

struct Edge{
	int idx, weight;
	Edge *next;
};
Edge adj[MaxN], memo[2*MaxN+10];
int mset;

int N,S, G[MaxN][51], nex[MaxN];
int L[MaxN][51];
bool vis[MaxN], use[MaxN];

void find( int now ){
	int i,k;
	Edge *ptr;
	use[now]=1;
	ptr=adj[now].next;
	while(ptr){
		k=ptr->idx;
		if(!use[k]){
			find(k);
			if(vis[k]) vis[now]=1;
		}
		ptr=ptr->next;
	}
}

void addEdge(int a, int b, int c){
	Edge *ptr=&memo[mset++];
	ptr->idx=b;
	ptr->weight=c;
	ptr->next=adj[a].next;
	adj[a].next=ptr;
}

void init(){
	int i,j,k,a ,b, c;
	scanf("%d%d",&N, &S);
	mset=0;
	for(i=1;i<=N;i++) adj[i].next=NULL;
	for(i=1;i<N;i++){
		scanf("%d%d%d",&a, &b, &c);
		addEdge(a, b, c);
		addEdge(b, a, c);
	}
	memset(vis, 0, sizeof vis);
	scanf("%d",&k);
	for(i=1;i<=k;i++){
		scanf("%d",&j);
		vis[j]=1;
	}
	memset(use, 0, sizeof use);
	find(S);
	memset(use, 0, sizeof use);
}

int DP(int now ){
	int i,j,k,ans[51],c, Max=0, sum=0;
	k=0;
	use[now]=1;
	Edge *ptr=adj[now].next;
	while(ptr){
		c=ptr->idx;
		if(vis[c]&&!use[c]){
			k++;
			ans[k]=DP(c)+ptr->weight;
			sum+=ans[k];
			if(ans[k]>Max) Max=ans[k];
		}
		ptr=ptr->next;
	}
	return 2*sum-Max;
}

void process(){
	int i,j,k;
	printf("%d\n",DP(S));
}

int main(){
	int i,j,k;
//	freopen("1935.in","r",stdin);
		init();
		process();
//	while(k=1);
	return 0;
}
