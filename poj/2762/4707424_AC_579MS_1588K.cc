#include <iostream>
#define UNVIS 0
#define VIS 1
#define OVER 2
#define MaxN 1050
using namespace std;

struct Edge
{
    int idx;
    Edge* next;
};
Edge adj[3][MaxN], memo[20000];

int N, M, cop, mset, lv;
int vis[MaxN];
int S[MaxN], sz;
int pre[MaxN], low[MaxN], id[MaxN];
int f[MaxN];
bool g[MaxN][MaxN];

void addEdge(int key, int a, int idx)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = idx;
    ptr->next = adj[key][a].next;
    adj[key][a].next = ptr;
}

void init()
{
    scanf("%d%d", &N, &M);
    mset = 0;
    for(int i=0; i<=N; ++i) adj[0][i].next = adj[1][i].next =adj[2][i].next = NULL;
    for(int i=0; i<M; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        addEdge(0, a, b);
    }
}

void dfs(int key, int now)
{
    id[now] = low[now] = lv++;
    S[++sz] = now; vis[now] = VIS;

    Edge * ptr = adj[key][now].next;
    while(ptr)
    {
        int k = ptr->idx;
        if(vis[k]==UNVIS)
        {
            dfs(key, k);
            if(low[k]<low[now]) low[now] = low[k];
        }
        else if(vis[k]==VIS)
        {
            if(low[k]<low[now]) low[now] = low[k];
        }
        ptr = ptr->next;
    }

    if(low[now]==id[now])
    {
        cop++;
        do
        {
            pre[S[sz]] = now;
            vis[S[sz]] = OVER;
        }while(S[sz--]!=now);
    }
}

void tarjan(int x)
{
    memset(vis, 0, sizeof vis);
    sz = lv = 0;
    for(int i=1; i<=N; ++i)
    {
        if(!vis[i]) dfs(0, i);
    }
}

int dp(int key, int now)
{
    if(f[now]!=-1) return f[now];

    int Max = 0;
    f[now] = 1;
    Edge * ptr = adj[key][now].next;
    
    while(ptr)
    {
        if(dp(key, ptr->idx) > Max) Max = dp(key, ptr->idx);
        ptr = ptr->next;
    }

    return f[now] = Max + 1;
}

void buildGraph()
{
    memset(g, 0, sizeof g);
    for(int i=1; i<=N; ++i)
    {
        Edge * ptr = adj[0][i].next;
        while(ptr)
        {
            int k = ptr->idx;
            if(pre[i]!=pre[k]&&!g[pre[i]][pre[k]])
            {
                g[pre[i]][pre[k]] = 1;
                addEdge(1, pre[i], pre[k]);
                addEdge(2, pre[k], pre[i]);
            }
            ptr = ptr->next;
        }
    }
}

void solve()
{
    cop = 0;
    tarjan(0);

    buildGraph();
    
    memset(f, -1, sizeof f);
    int k1 = dp(1, 1);
    memset(f, -1, sizeof f);
    int k2 = dp(2, 1);
    int res = k1+k2-1;
    if(res==cop) printf("Yes\n");
    else printf("No\n");
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        init();
        solve();
    }
    return 0;
}

