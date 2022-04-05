#include <iostream>
#define INF 1000000000
#define MaxL 300
using namespace std;

struct Edge
{
    int idx, f;
    Edge * next, *opp;
}
adj[MaxL], memo[MaxL*MaxL];

Edge * pre[MaxL];

int K, C, M, mset, S, T;
int g[MaxL][MaxL];
int Q[MaxL], head, tail, lv[MaxL];

void addEdgeProcess(int a, int b, int c)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->f = c;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void addEdge(int a, int b, int c)
{
    addEdgeProcess(a, b, c);
    addEdgeProcess(b, a, 0);
    adj[a].next->opp = &memo[mset-1];
    adj[b].next->opp = &memo[mset-2];
}

void init()
{
    scanf("%d%d%d", &K, &C, &M);
    for(int i=0; i<K+C; ++i)
        for(int j=0; j<K+C; ++j)
        {
            scanf("%d", &g[i][j]);
            if(g[i][j]==0) g[i][j] = INF;
        }
    for(int k=0; k<K+C; ++k)
        for(int i=0; i<K+C; ++i)
            for(int j=0; j<K+C; ++j)
                if(g[i][k]+g[k][j]<g[i][j])
                    g[i][j] = g[i][k] + g[k][j];
}

void buildGraph(int LIM)
{
    S = K+C; T = S+1;

    mset = 0;
    for(int i=0; i<=T; ++i) adj[i].next = NULL;

    for(int i=K; i<K+C; ++i)
        for(int j=0; j<K; ++j)
            if(g[i][j]<=LIM) addEdge(i, j, 1);
    for(int i=K; i<K+C; ++i) addEdge(S, i, 1);
    for(int i=0; i<K; ++i) addEdge(i, T, M);
}

int Min(int a, int b){ return (a<b)?a:b; }

bool bfs(int S, int T)
{
    memset(lv, -1, sizeof lv);
    Q[head = tail = 1] = S;
    lv[S] = 1;
    while(head<=tail)
    {
        int k = Q[head];
        Edge * ptr = adj[k].next;
        while(ptr)
        {
            if(ptr->f>0&&lv[ptr->idx]==-1)
            {
                Q[++tail] = ptr->idx;
                pre[ptr->idx] = ptr;
                lv[ptr->idx] = 1;
            }
            ptr = ptr->next;
        }
        head++;
    }
    return lv[T]==1;
}

int max_flow(int S, int T)
{
    int flow = 0;
    while(bfs(S, T))
    {
        int tmp = INF;
        int k = T;
        while(k!=S)
        {
            tmp = Min(tmp, pre[k]->f);
            k = pre[k]->opp->idx;
        }
        k = T;
        flow += tmp;
        while(k!=S)
        {
            pre[k]->f -= tmp;
            pre[k]->opp->f += tmp;
            k = pre[k]->opp->idx;
        }
    }
    return flow;
}

bool check(int x)
{
    buildGraph(x);
    if(max_flow(S, T)==C) return 1;
    else return 0;
}

void solve()
{
    int l=0, r=INF-1, mid, ans = -1;
    while(l<=r)
    {
        mid = (l+r)>>1;
        if(check(mid))
        {
            ans = mid;
            r = mid-1;
        }
        else l = mid+1;
    }
    printf("%d\n", ans);
}

int main()
{
    init();
    solve();
    return 0;
}

