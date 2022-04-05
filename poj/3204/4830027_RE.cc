#include <iostream>
#define MaxL 600
#define INF 100000000
using namespace std;

struct Edge
{
    int idx, f;
    Edge *next, *opp;
}
adj[MaxL], memo[MaxL*MaxL];

bool vis[MaxL];
int N, M, mset;
int Q[MaxL], head, tail, Path[MaxL], top;
int lv[MaxL];
Edge *pre[MaxL], *cur[MaxL];

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

    mset = 0;
    for(int i=0; i<N; ++i) adj[i].next = NULL;

    for(int i=0; i<M; ++i)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        addEdge(a, b, c);
    }
}

bool bfs(int S, int T)
{
    memset(lv, -1, sizeof lv);
    Q[head=tail] = S;
    lv[S] = 1;
    while(head<=tail)
    {
        int k = Q[head];
        Edge * ptr = adj[k].next;
        while(ptr)
        {
            if(lv[ptr->idx]==-1&&ptr->f>0)
            {
                lv[ptr->idx] = lv[k] + 1;
                Q[++tail] = ptr->idx;
            }
            ptr = ptr->next;
        }
        ++head;
    }
    return lv[T]!=-1;
}

int Min(int a, int b){ return (a<b)?a:b; }

int max_flow(int S, int T)
{
    int u, flow = 0;
    while(bfs(S, T))
    {
        Path[top = 1] = u = S;
        for(int i=0; i<2*N; ++i) cur[i] = adj[i].next;
        while(cur[S])
        {
            if(u!=T&&cur[u]&&cur[u]->f>0&&lv[cur[u]->idx]==lv[u]+1)
            {
                int v = cur[u]->idx;
                pre[v] = cur[u];
                Path[++top] = v;
                u = v;
            }
            else if(u==T)
            {
                int tmp = INF;
                for(int i=top; i>1; --i) tmp = Min(tmp, pre[Path[i]]->f);
                for(int i=top; i>1; --i)
                {
                    pre[Path[i]]->f -= tmp;
                    pre[Path[i]]->opp->f += tmp;
                    if(pre[Path[i]]->f==0) top = i-1;
                }
                u = Path[top];
                flow += tmp;
            }
            else
            {
                while(u!=S&&cur[u]==NULL) u = Path[--top];
                cur[u] = cur[u]->next;
            }
        }
    }
    return flow;
}

void dfs(int now)
{
    vis[now] = 1;
    Edge * ptr = adj[now].next;
    while(ptr)
    {
        if(ptr->f>0&&!vis[ptr->idx]) dfs(ptr->idx);
        ptr = ptr->next;
    }
}

int cnt()
{
    int ans = 0;
    for(int i=0; i<N; ++i)
    {
        if(!vis[i]) continue;
        Edge * ptr = adj[i].next;
        while(ptr)
        {
            if(vis[ptr->idx]==0) ans++;
            ptr = ptr->next;
        }
    }
    return ans;
}

void solve()
{
    max_flow(0, N-1);
    memset(vis, 0, sizeof vis);
    dfs(0);
    int k = cnt();
    printf("%d\n", k);
}

int main()
{
    while(scanf("%d%d", &N, &M))
    {
        init();
        solve();
    }
    return 0;
}

