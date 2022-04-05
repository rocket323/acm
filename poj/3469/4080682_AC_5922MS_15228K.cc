#include <iostream>
#define MaxL 10000000
#define MaxN 41000
using namespace std;

struct Edge{
    int idx, flow;
    Edge *next;
    Edge *opp;
};

Edge adj[MaxN], memo[40*MaxN];
int Path[MaxN], top;
int Lv[MaxN], Q[MaxN];
int N, M, mset, S, T;
Edge *cur[MaxN];
Edge *Ed[MaxN];

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

void init(){
    int i, a, b, c;
    mset=0;
    S=0; T=N+N+1;
    for(i=S; i<=T; ++i){ adj[i].next=NULL; adj[i].opp=NULL; }
    for(i=1; i<=N; ++i){
        scanf("%d%d", &a, &b);
        addEdge(S, i, a); addEdge(i, T, b);
    }
    for(i=1; i<=M; ++i){
        scanf("%d%d%d", &a, &b, &c);
        addEdge(a, b, c);
        addEdge(b, a, c);
    }
}

bool bfs(int S, int T){
    int head, tail, k, p;
    Edge *ptr;
    memset(Lv, -1, sizeof Lv);
    Q[head=tail=1]=S; Lv[S]=0;
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
    return (Lv[T]!=-1);
}

int min(int a, int b){
	return (a<b)?a:b;
}

int Dinic(int S, int T){
    int flow=0, i, Min, u, v;
    while(bfs(S, T)){
        top=1; Path[top]=u=S;
        for(i=S; i<=T; ++i) cur[i]=adj[i].next;
        while(cur[S]){
            if(u!=T&&cur[u]&&cur[u]->flow>0&&Lv[cur[u]->idx]==Lv[u]+1){
				top++; v=cur[u]->idx;
                Path[top]=v;
                Ed[top]=cur[u];
                u=v;
            }
            else if(u==T){
                Min=MaxL+1;
                for(i=top; i>1; --i) Min=min(Min, Ed[i]->flow);	
                for(i=top; i>1; --i){
                    Ed[i]->flow-=Min;
                    Ed[i]->opp->flow+=Min;
                    if(Ed[i]->flow==0) top=i-1;
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
//    freopen("3469.in", "r", stdin);
    while(scanf("%d%d", &N, &M)!=EOF){
        init();
        printf("%d\n", Dinic(S, T));
    }
//    while(1);
    return 0;
}
