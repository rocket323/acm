#include <iostream>
#define MaxN 201
#define MaxL 10000000
using namespace std;

struct Edge{
	int idx, flow;
	Edge* next;
	Edge* opp;
};
Edge adj[MaxN], memo[4*MaxN];

int N, M, mset=0, Path[MaxN], top;
int Q[MaxN], Lv[MaxN];
Edge *pre[MaxN], *cur[MaxN];

void addEdgeProcess(int a, int b, int c){
	Edge* ptr=&memo[mset++];
	ptr->idx=b; ptr->flow=c;
	ptr->next=adj[a].next;
	adj[a].next=ptr;
}

void addEdge(int a, int b, int c){
	addEdgeProcess(a, b, c);
	addEdgeProcess(b, a, 0);
	adj[a].next->opp=&memo[mset-1];
	adj[b].next->opp=&memo[mset-2];
}

void init(){
	int i,j,k, a, b, c;
	for(i=1; i<=N; ++i){ adj[i].next=NULL; adj[i].opp=NULL; }
	mset=0;
	for(i=1; i<=M; ++i){
		scanf("%d%d%d", &a, &b, &c);
		addEdge(a, b, c);
	}
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

int Dinic(int S, int T){
	int i,j,k, flow=0, Min, u, v;
	while(bfs(S, T)){
		top=1; Path[top]=u=S;
		for(i=1; i<=N; ++i) cur[i]=adj[i].next;
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

int main(){
	int i,j,k;
//	freopen("1273.in", "r", stdin);
	while(scanf("%d%d", &M, &N)!=EOF){
		init();
		printf("%d\n", Dinic(1, N));
	}
//	while(1);
	return 0;
}
