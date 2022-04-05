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
int Path[MaxN], top;
Edge *pre[MaxN], *cur[MaxN];
int Lv[MaxN];
int Q[MaxN], lastFlow;

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
	Edge *ptr=&memo[mset++];
	ptr->idx=b; ptr->flow=c;
	ptr->next=adj[a].next;
	adj[a].next=ptr;
}

void addEdgeProcess(int a, int b, int c){
	addEdge(a, b, c); addEdge(b, a, 0);
	adj[a].next->opp=&memo[mset-1];
	adj[b].next->opp=&memo[mset-2];
}

int min(int a, int b){
	return (a<b)?a:b;
}

bool bfs(int S, int T){
	int head, tail;
	Edge* ptr;
	memset(Lv, -1, sizeof Lv);
	Q[head=tail=1]=S; Lv[S]=0;
	while(head<=tail){
		int k=Q[head];
		ptr=adj[k].next;
		while(ptr){
			int p=ptr->idx;
			if(Lv[p]==-1&&ptr->flow>0){
				Lv[p]=Lv[k]+1;
				Q[++tail]=p;
			}
			ptr=ptr->next;
		}
		head++;
	}
	return (Lv[T]!=-1);
}	

int MaxFlow(int S, int T){
	int i,j,k, flow=0, Min, u, v;
	while(bfs(S, T)){
		top=1; Path[top]=u=S;
		for(i=S; i<=T; ++i) cur[i]=adj[i].next;
		while(cur[S]){
			if(u!=T&&cur[u]&&cur[u]->flow>0&&Lv[cur[u]->idx]==Lv[u]+1){
				top++; v=cur[u]->idx;
				Path[top]=v;
				pre[v]=cur[u];
				u=v;
			}
			else if(u==T){
				Min=MaxL;
				for(i=top; i>1; --i) Min=min(Min, pre[Path[i]]->flow);
				for(i=top; i>1; --i){
					pre[Path[i]]->flow-=Min;
					pre[Path[i]]->opp->flow+=Min;
					if(pre[Path[i]]->flow==0) top=i-1;
				}
				u=Path[top];
				flow+=Min;
			}
			else {
				while(u!=S&&cur[u]==NULL) u=Path[--top];
				cur[u]=cur[u]->next;
			}
		}
	}
	return flow;
}

void makeGra(int low, int high){
	int i,j,k;
	mset=0;
	for(i=0; i<=N+B+2; ++i){ adj[i].next=NULL; adj[i].opp=NULL; }
	for(i=1; i<=N; ++i){
		addEdgeProcess(S, i, 1);
	}
	for(i=1; i<=N; ++i)
		for(j=1; j<=B; ++j)
			if(low<=pri[i][j]&&pri[i][j]<=high){
				addEdgeProcess(i, j+N, 1);
			}
	for(j=N+1; j<=N+B; ++j){
		addEdgeProcess(j, T, C[j-N]);
	}
}

void addGra(int high){
	int i,j;
	for(i=1; i<=N; ++i)
		for(j=1; j<=B; ++j)
			if(pri[i][j]==high)
				addEdgeProcess(i, j+N, 1);
}

bool check(int low, int high, int tt){
	int i,j,k, newFlow;
	if(tt==1){
		makeGra(low, high);
		lastFlow=0;
	}
	else addGra(high);
	newFlow=MaxFlow(S, T);
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
			tt=1;
		}
	}
	printf("%d\n", len);	
}

int main(){
//	freopen("stead.6.in", "r", stdin);
	int i,j,k;
	init();
	process();
//	while(1);
	return 0;
}
