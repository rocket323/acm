#include <iostream>
#define MaxN 1030
#define MaxL 10000000
using namespace std;

struct Edge{
	int idx, flow;
	Edge* next;
	Edge* opp;	
};
Edge adj[MaxN], memo[60000];

int N, B, M, pri[1001][21], C[21], S, T, mset;
Edge* pre[MaxN];
int Q[MaxN], lastFlow;
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
	S=0; T=N+B+1;
	for(i=1; i<=B; ++i) scanf("%d", &C[i]);
	lastFlow=0;
}

void addEdge(int a, int b, int c){
	Edge* p1;
	Edge* p2;
	p1=&memo[mset++]; p2=&memo[mset++];
	p1->idx=b; p2->idx=a;
	p1->flow=c; p2->flow=0;
	p1->opp=p2;
	p2->opp=p1;
	p1->next=adj[a].next;
	p2->next=adj[b].next;
	adj[a].next=p1; adj[b].next=p2;
}

bool bfs(){
	int i,j,k,p, head, tail;
	Edge *ptr;
	memset(lt, 0, sizeof lt);
	Q[head=tail=1]=S; lt[S]=1;
	for(i=0; i<=N; ++i) pre[i]=NULL;
	while(head<=tail){
		k=Q[head];
		ptr=adj[k].next;
		while(ptr){
			p=ptr->idx;
			if(!lt[p]&&ptr->flow>0){
				lt[p]=1;
				Q[++tail]=p;
				pre[p]=ptr;
				if(p==T) return true;
			}
			ptr=ptr->next;
		}
		head++;
	}
	return lt[T];
}

int MaxFlow(int low, int high){
	int i,j,k, Min, ans=0;
	Edge* ptr;
	while(bfs()){
		k=T; Min=MaxL;
		while(k!=S){
			if(Min>pre[k]->flow) Min=pre[k]->flow;
			ptr=pre[k]->opp;
			k=ptr->idx;
		}
		ans+=Min;
		k=T;
		while(k!=S){
			pre[k]->flow-=Min;
			ptr=pre[k]->opp;
			ptr->flow+=Min;
			k=ptr->idx;
		}
	}
	return ans;
}

void makeGra(int low, int high){
	int i,j,k;
	mset=0;
	for(i=0; i<=N+B+2; ++i) adj[i].next=NULL;
	for(i=1; i<=N; ++i){
		addEdge(S, i, 1);
	}
	for(i=1; i<=N; ++i)
		for(j=1; j<=B; ++j)
			if(low<=pri[i][j]&&pri[i][j]<=high){
				addEdge(i, j+N, 1);
			}
	for(j=N+1; j<=N+B; ++j){
		addEdge(j, T, C[j-N]);
	}
}

void addGra(int high){
	int i,j;
	for(i=1; i<=N; ++i)
		for(j=1; j<=B; ++j)
			if(pri[i][j]==high)
				addEdge(i, j+N, 1);
}

bool check(int low, int high, int tt){
	int i,j,k, newFlow;
	if(tt==1){
		makeGra(low, high);
		lastFlow=0;
	}
	else addGra(high);
	newFlow=MaxFlow(low, high);
	k=lastFlow+newFlow; lastFlow=k;
	if(k==N) return true;
	else return false;
}

void process(){
	int i,j,k, low=1, high=1, len=MaxL;
	int tt=1;
	while(low<=high&&high<=B){
		if(check(low, high, tt)){
			if(high-low+1<len) len=high-low+1;
			low++;
			tt=1;
		}
		else{
			high++;
			tt=2;
		}
	}
	printf("%d\n", len);	
}

int main(){
	int i,j,k;
//	freopen("stead.7.in", "r", stdin);
//	freopen("oo.out", "w", stdout);
	init();

	process();
//	while(1);
	return 0;
}
