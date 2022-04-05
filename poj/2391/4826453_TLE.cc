#include <iostream>
#include <string>
#define MaxL 300
#define INF 100000000
using namespace std;

struct Edge
{
    int idx, f;
    Edge * next, * opp;
}
adj[MaxL], memo[MaxL*MaxL];

Edge * pre[MaxL], * cur[MaxL];

int sum, F, P, c[MaxL], f[MaxL];
int g[MaxL][MaxL], mset;
int lv[MaxL], Q[MaxL], top, Path[MaxL], head, tail, S, T;

int Min(int a, int b){ return (a<b)?a:b; }

void init()
{
    scanf("%d%d", &F, &P);
    sum = 0;
    for(int i=0; i<F; ++i){ scanf("%d%d", &c[i], &f[i]); sum += c[i]; }
    for(int i=0; i<F; ++i)
        for(int j=0; j<F; ++j)
            g[i][j] = INF;
    for(int i=0; i<P; ++i)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        if(c<g[a][b]) g[a][b] = g[b][a] = c;
    }

    for(int k=0; k<F; ++k)
        for(int i=0; i<F; ++i)
            for(int j=0; j<F; ++j)
                if(g[i][k] + g[k][j] < g[i][j])
                    g[i][j] = g[i][k] + g[k][j];

    S = 2*F; T =S+1;
}

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

void buildGraph(int x)
{
    mset = 0;
    for(int i=0; i<=T; ++i) adj[i].next = NULL;

    for(int i=0; i<F; ++i)
        for(int j=0; j<F; ++j)
            if(g[i][j]<=x) addEdge(i, j+F, c[i]);

    for(int i=0; i<F; ++i) addEdge(S, i, c[i]);
    for(int i=0; i<F; ++i) addEdge(i+F, T, f[i]);
}

bool bfs(int S, int T)
{
    memset(lv, -1, sizeof lv);
    Q[head=tail=1] = S;
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

int max_flow(int S, int T)
{
    int u, flow = 0;
    while(bfs(S, T))
    {
        Path[top=1] = u = S;
        for(int i=0; i<=T; ++i) cur[i] = adj[i].next;
        while(cur[S])
        {
            if(u!=T&&cur[u]&&cur[u]->f>0&&lv[cur[u]->idx]==lv[u]+1)
            {
                int v = cur[u]->idx;
                Path[++top] = v;
                pre[v] = cur[u];
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

bool check(int x)
{
    buildGraph(x);
    if(max_flow(S, T) >= sum) return 1;
    else return 0;
}

void solve()
{
    int l=0, r=INF, mid, ans = -1;

    while(l<=r)
    {
        mid = (l+r)>>1;
        if(check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    printf("%d\n", ans);
}

int main()
{
    init();
    solve();
    return 0;
}

