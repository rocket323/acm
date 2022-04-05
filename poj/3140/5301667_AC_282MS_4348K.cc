#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#define INF 1000000000000000LL
#define ll long long
#define MaxL 100010

struct Edge
{
    int idx;
    Edge *next;
}
adj[MaxL], memo[20 * MaxL];

int n, m, a[MaxL], mset, p[MaxL];
long long S[MaxL], sum;

void addEdge(int a, int b)
{
    Edge *ptr = &memo[mset++];
    ptr->idx = b;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void init()
{
    mset = sum = 0;
    for(int i=0; i<=n; ++i) adj[i].next = NULL;
    for(int i=1; i<=n; ++i)
    {
        scanf("%d", &a[i]);
        sum += a[i];
    }

    for(int i=0; i<m; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
}

void dfs(int now)
{
    S[now] = a[now];
    for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
    {
        if(p[now] != ptr->idx)
        {
            p[ptr->idx] = now;
            dfs(ptr->idx);
            S[now] += S[ptr->idx];
        }
    }
}

void solve(int cs)
{
    memset(p, -1, sizeof p);
    dfs(1);
    long long ans = INF;
    for(int i=1; i<=n; ++i)
    {
        long long k;
        k = (ll)S[i] * 2 - sum;
        if(k < 0) k = -k;
        if(k < ans) ans = k;
    }
    printf("Case %d: %I64d\n", cs, ans);
}

int main()
{
    int t = 0;
    while(scanf("%d%d", &n, &m) && (n + m))
    {
        init();
        solve(++t);
    }
    return 0;
}
