#include <iostream>
#define MaxN 100010
#define INF 2001000000
#define ll long long
using namespace std;

struct Edge
{
    ll idx;
    Edge * next;
};
Edge adj[MaxN], memo[10*MaxN];

ll N, M, mset, C[MaxN];
ll f[MaxN], Q[MaxN], len;
ll res;
ll in[MaxN], out[MaxN], S[MaxN], sz;

void addEdge(ll a, ll idx)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = idx;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void init()
{
    mset = 0;
    for(ll i=1; i<=N; ++i) adj[i].next = NULL;
    memset(in, 0, sizeof in);
    memset(out, 0, sizeof out);

    for(ll i=1; i<=N; ++i) scanf("%I64d", &C[i]);
    for(ll i=0; i<M; ++i)
    {
        ll a, b;
        scanf("%I64d%I64d", &a, &b);
        addEdge(a, b);
        in[b]++;
        out[a]++;
    }
}

void dp()
{
    for(ll i=1; i<=len; ++i)
    {
        Edge * ptr = adj[Q[i]].next;
        while(ptr)
        {
            ll k = ptr->idx;
            if(f[Q[i]]!=-INF&&f[k]<f[Q[i]]+C[k]) f[k] = f[Q[i]] + C[k];
            ptr = ptr->next;
        }
    }
}

void topSort()
{
    sz = 0;
    for(ll i=1; i<=N; ++i)
        if(in[i]==0) S[++sz] = i;

    len = 0;
    for(ll i=1; i<=N; ++i)
    {
        ll k = S[sz--];
        Q[++len] = k;
        f[k] = C[k];
        for(Edge* ptr=adj[k].next; ptr; ptr=ptr->next)
        {
            in[ptr->idx]--;
            if(in[ptr->idx]==0) S[++sz] = ptr->idx;
        }
    }
}

void solve()
{
    res = -INF;

    for(ll i=1; i<=N; ++i) f[i] = -INF;
    topSort();

    dp();
    
    for(ll i=1; i<=N; ++i)
        if(out[i]==0&&res<f[i]) res = f[i];

    printf("%I64d\n", res);
}

int  main()
{
    while(scanf("%I64d%I64d", &N, &M)!=EOF)
    {
        init();
        solve();
    }
    return 0;
}

