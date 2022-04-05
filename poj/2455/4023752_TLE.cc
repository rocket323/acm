#include <iostream>
#define MaxL 100000000
using namespace std;

struct Edge{
	int idx, flow;
	Edge* next;
	Edge* opp;
};
Edge adj[201], memo[160010];

int Ea[40001], Eb[40001], L[40001], N, M, T, mset;
int Path[201], top, Q[201];
int Lv[201];
Edge *pre[201], *cur[201];

void init(){
	int i,j,k;
	scanf("%d%d%d", &N, &M, &T);
	for(i=1; i<=M; ++i) scanf("%d%d%d", &Ea[i], &Eb[i], &L[i]);
}

void addEdgeProcess(int a, int b, int c){
	Edge *ptr=&memo[mset++];
	ptr->idx=b; ptr->flow=c;
	ptr->next=adj[a].next;
	adj[a].next=ptr;
}

void addEdge(int a, int b, int c){
	addEdgeProcess(a, b, c);
	addEdgeProcess(b, a, 0);
	adj[a].next->opp=adj[b].next;
	adj[b].next->opp=adj[a].next;
}

bool bfs(){
	int head, tail, i, j, k, p;
	Edge *ptr;
	Q[head=tail=1]=1;
	memset(Lv, -1, sizeof Lv);
	Lv[1]=0;
	while(head<=tail){
		k=Q[head];
		ptr=adj[k].next;
		while(ptr){
			p=ptr->idx;
			if(Lv[p]==-1&&ptr->flow>0){
				Q[++tail]=p;
				Lv[p]=Lv[k]+1;
			}
			ptr=ptr->next;
		}
		head++;
	}
	return (Lv[N]!=-1);
}

int Dinic(int check){
	int i,j,k, flow=0, u, v, Min;
	mset=0;
	for(i=1; i<=N; ++i){ adj[i].next=NULL; adj[i].opp=NULL; }
	for(i=1; i<=M; ++i){
		if(L[i]<=check){
			addEdge(Ea[i], Eb[i], 1);
			addEdge(Eb[i], Ea[i], 1);
		}
	}
	while(bfs()){
		u=Path[top=1]=1;
		for(i=1; i<=N; ++i) cur[i]=adj[i].next;
		while(cur[1]){
			if(u!=N&&cur[u]&&cur[u]->flow>0&&Lv[cur[u]->idx]==Lv[u]+1){
				v=cur[u]->idx;
				Path[++top]=v;
				pre[top]=cur[u];
				u=v;
			}
			else if(u==N){
				Min=MaxL;
				for(i=top; i>1; --i) Min=min(Min, pre[i]->flow);
				flow+=Min;
				for(i=top; i>1; --i){
					pre[i]->flow-=Min;
					pre[i]->opp->flow+=Min;
					if(pre[i]->flow==0) top=i-1;
				}
				u=Path[top];
			}
			else {
				while(u!=1&&cur[u]==NULL) u=Path[--top];
				cur[u]=cur[u]->next;
			}
		}
	}
	return flow;
}

void process(){
	int i,j,k, l, r, mid;
	int ans=MaxL;
	l=0; r=1000001;
	while(l<=r){
		mid=(l+r)>>1;
		if(Dinic(mid)>=T){
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
	printf("%d\n", ans);
}

int main(){
	int i,j,k;
//	freopen("2455.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
