#include <iostream>
#define MaxN 1001
#define UNVIS 0
#define VIS 1
#define OVER 2
using namespace std;

struct Edge
{
    int idx;
    Edge* next;
}adj[MaxN], memo[300*MaxN];

int N, mset, lv;
int pre[MaxN];
int vis[MaxN];
int id[MaxN], low[MaxN];
int S[MaxN], sz;
int in[MaxN], out[MaxN];

void addEdge(int a, int idx)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = idx;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void init()
{
    scanf("%d", &N);
    mset = 0;
    for(int i=0; i<=N; ++i) adj[i].next = NULL;
    for(int i=1; i<=N; ++i)
    {
        int b;
        while(scanf("%d", &b) && b) addEdge(i, b);
    }
}

void dfs(int now)
{
    S[++sz] = now;
    vis[now] = VIS;
    low[now] = id[now] = sz++;
    
    Edge * ptr = adj[now].next;
    while(ptr)
    {
        int k = ptr->idx;
        if(vis[k]==UNVIS)
        {
            dfs(k);
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
        do
        {
            pre[S[sz]] = now;
            vis[S[sz]] = OVER;
        }while(S[sz--]!=now);
    }
}

void Tarjan()
{
    memset(vis, 0, sizeof vis);
    sz = 0; lv = 0;
    for(int i=1; i<=N; ++i)
    {
        if(vis[i]==UNVIS) dfs(i);
    }
}

int Max(int a, int b){ return (a>b)?a:b; }

void solve()
{
    Tarjan();
    memset(in, 0, sizeof in);
    memset(out, 0, sizeof out);
    for(int i=1; i<=N; ++i)
    {
        int a = pre[i];
        Edge* ptr = adj[i].next;
        while(ptr)
        {
            int b = pre[ptr->idx];
            if(a!=b)
            {
                out[a]++;
                in[b]++;
            }
            ptr = ptr->next;
        }
    }

    int idd=0, odd=0, cnt = 0;
    for(int i=1; i<=N; ++i)
    {
        if(pre[i]!=i) continue;
        if(in[i]==0) idd++;
        if(out[i]==0) odd++;
        ++cnt;
    }
    if(cnt==1) { printf("1\n0\n"); return; }
    printf("%d\n%d\n", idd, Max(idd, odd));
}

int main()
{
    init();
    solve();
    return 0;
}

