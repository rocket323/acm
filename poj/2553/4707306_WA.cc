#include <iostream>
#define MaxN 6000
#define UNVIS 0
#define VIS 1
#define OVER 2
using namespace std;

struct Edge
{
    int idx;
    Edge* next;
}adj[MaxN], memo[300*MaxN];

int N, M, mset, lv;
int low[MaxN], id[MaxN], vis[MaxN];
int S[MaxN], sz;
int pre[MaxN];
int res[MaxN], top;

void addEdge(int a, int b)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void init()
{
    mset = 0;
    for(int i=1; i<=N; ++i) adj[i].next = NULL;
    for(int i=0; i<M; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        addEdge(a, b);
    }
}

void dfs(int now)
{
    id[now] = low[now] = lv++;
    vis[now] = VIS;
    S[++sz] = now;

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

    if(low[now] == id[now])
    {
        do
        {
            pre[S[sz]] = now;
            vis[S[sz]] = OVER;
        }while(S[sz--]!=now);
    }
}

void tarjan()
{
    memset(vis, 0, sizeof vis);
    sz = 0; lv = 0;
    for(int i=1; i<=N; ++i)
    {
        if(!vis[i]) dfs(i);
    }
}

void solve()
{
    tarjan();
    top = 0;
    for(int i=1; i<=N; ++i)
    {
        bool flag = 1;
        Edge * ptr = adj[i].next;
        while(ptr)
        {
            int k = ptr->idx;
            if(pre[k]!=pre[i])
            {
                flag = 0;
                break;
            }
            ptr = ptr->next;
        }
        if(flag) res[top++] = i;
    }
    if(top==0) printf("\n");
    else
    {
        for(int i=0; i<top-1; ++i) printf("%d ", res[i]);
        printf("%d\n", res[top-1]);
    }
}

int main()
{
    while(scanf("%d", &N) && N)
    {
        scanf("%d", &M);
        init();
        solve();
    }
    return 0;
}

