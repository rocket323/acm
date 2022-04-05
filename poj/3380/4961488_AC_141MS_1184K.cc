#include <iostream>
#include <algorithm>
#define MaxL 10010
#define ll long long
using namespace std;

struct Edge
{
    int idx;
    Edge * next;
}
adj[MaxL], memo[2*MaxL];

struct node
{
    int a, b, lv;
    ll w;
}E[MaxL];

int n, k, h, c, sz[MaxL], mset;
int p[MaxL];

void addEdge(int a, int b)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void dfs(int now)
{
    sz[now] = 1;
    Edge * ptr = adj[now].next;
    while(ptr)
    {
        int k = ptr->idx;
        if(p[now]!=k)
        {
            p[k] = now;
            dfs(k);
            sz[now] += sz[k];
        }
        ptr = ptr->next;
    }
}

int cmp1(node A, node B){ return (A.w > B.w); }
int cmp2(node A, node B){ return (A.w < B.w); }

void init()
{
    scanf("%d%d%d%d", &n, &k, &h, &c);
    mset = 0;
    for(int i=0; i<=n; ++i) adj[i].next = NULL;
    for(int i=1; i<n; ++i)
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        addEdge(a, b);
        addEdge(b, a);
        E[i].a = a; E[i].b = b; E[i].lv = i; E[i].w = w;
    }
}

void solve()
{
    memset(p, -1, sizeof p);
    dfs(1);

    for(int i=1; i<n; ++i)
    {
        if(p[E[i].a]==E[i].b)
        {
            int t=E[i].a; E[i].a=E[i].b; E[i].b=t;
        }

        E[i].w = (ll)E[i].w * sz[E[i].b] * (n - sz[E[i].b]);
    }
    if(h < c) sort(E+1, E+n, cmp1);
    else sort(E+1, E+n, cmp2);
    for(int i=1; i<k; ++i) printf("%d ", E[i].lv);
    printf("%d\n", E[k].lv);
}

int main()
{
    init();
    solve();
    return 0;
}

