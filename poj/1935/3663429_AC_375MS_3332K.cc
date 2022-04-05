#include <iostream>
#define MaxN 50001
#define MaxL 100000000
using namespace std;

struct Edge{
	int idx, weight;
	Edge *next;
};
Edge adj[MaxN], memo[2*MaxN+10];
int mset;

int N,S, M[MaxN],L[MaxN], Sum[MaxN];
bool vis[MaxN], use[MaxN];

void find( int now ){
	int i,k;
	Edge *ptr;
	use[now]=1; Sum[now]=0;
	ptr=adj[now].next;
	while(ptr){
		k=ptr->idx;
		if(!use[k]){
			find(k);
			if(vis[k]){
				vis[now]=1;
				Sum[now]+=2*(ptr->weight)+Sum[k];
			}
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
	memset(M, 0, sizeof M);
}

int DP(int now ){
	int i,j,k,c, Min=MaxL, sum=0, ans, rec=0;
	k=0;
	use[now]=1;
	Edge *ptr=adj[now].next;
	while(ptr){
		c=ptr->idx;
		if(vis[c]&&!use[c]){
			ans=(Sum[now]-Sum[c]-ptr->weight)+DP(c);
			if(ans<Min){
				Min=ans;
			}
		}
		ptr=ptr->next;
	}
	if(Min==MaxL) Min=0;
	return Min;
}

void process(){
	int i,j,k,ans;
	ans=DP(S);
	printf("%d",ans);
}

int main(){
	int i,j,k;
	init();
	process();
	return 0;
}
