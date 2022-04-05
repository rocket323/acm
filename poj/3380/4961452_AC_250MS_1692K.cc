#include <iostream>
#include <algorithm>
#define MaxL 10010
#define ll long long
using namespace std;

struct Edge
{
    ll idx;
    Edge * next;
}
adj[MaxL], memo[2*MaxL];

struct node
{
    ll a, b, w, lv;
}E[MaxL];

ll n, k, h, c, sz[MaxL], mset;
ll p[MaxL];

void addEdge(ll a, ll b)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void dfs(ll now)
{
    sz[now] = 1;
    Edge * ptr = adj[now].next;
    while(ptr)
    {
        ll k = ptr->idx;
        if(p[now]!=k)
        {
            p[k] = now;
            dfs(k);
            sz[now] += sz[k];
        }
        ptr = ptr->next;
    }
}

ll cmp1(node A, node B){ return (A.w > B.w); }
ll cmp2(node A, node B){ return (A.w < B.w); }

void init()
{
    scanf("%I64d%I64d%I64d%I64d", &n, &k, &h, &c);
    mset = 0;
    for(ll i=0; i<=n; ++i) adj[i].next = NULL;
    for(ll i=1; i<n; ++i)
    {
        ll a, b, w;
        scanf("%I64d%I64d%I64d", &a, &b, &w);
        addEdge(a, b);
        addEdge(b, a);
        E[i].a = a; E[i].b = b; E[i].lv = i; E[i].w = w;
    }
}

void solve()
{
    memset(p, -1, sizeof p);
    dfs(1);

    for(ll i=1; i<n; ++i)
    {
        if(p[E[i].a]==E[i].b)
        {
            ll t=E[i].a; E[i].a=E[i].b; E[i].b=t;
        }

        E[i].w = (ll)E[i].w * sz[E[i].b] * (n - sz[E[i].b]);
    }
    if(h < c) sort(E+1, E+n, cmp1);
    else sort(E+1, E+n, cmp2);
    for(ll i=1; i<k; ++i) printf("%I64d ", E[i].lv);
    printf("%I64d\n", E[k].lv);
}

int main()
{
    init();
    solve();
    return 0;
}

