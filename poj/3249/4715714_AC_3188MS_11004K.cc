#include <iostream>
#define MaxN 100010
#define INF 2001000000
using namespace std;

struct Edge
{
    int idx;
    Edge * next;
};
Edge adj[MaxN], memo[10*MaxN];

int N, M, mset, C[MaxN];
int f[MaxN], Q[MaxN], len;
int res;
int in[MaxN], out[MaxN], S[MaxN], sz;

void addEdge(int a, int idx)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = idx;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void init()
{
    mset = 0;
    for(int i=1; i<=N; ++i) adj[i].next = NULL;
    memset(in, 0, sizeof in);
    memset(out, 0, sizeof out);

    for(int i=1; i<=N; ++i) scanf("%d", &C[i]);
    for(int i=0; i<M; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        addEdge(a, b);
        in[b]++;
        out[a]++;
    }
}

void dp()
{
    for(int i=1; i<=len; ++i)
    {
        Edge * ptr = adj[Q[i]].next;
        while(ptr)
        {
            int k = ptr->idx;
            if(f[Q[i]]!=-INF&&f[k]<f[Q[i]]+C[k]) f[k] = f[Q[i]] + C[k];
            ptr = ptr->next;
        }
    }
}

void topSort()
{
    sz = 0;
    for(int i=1; i<=N; ++i)
        if(in[i]==0)
        {
            S[++sz] = i;
            f[i] = C[i];
        }

    len = 0;
    for(int i=1; i<=N; ++i)
    {
        int k = S[sz--];
        Q[++len] = k;
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

    for(int i=1; i<=N; ++i) f[i] = -INF;
    topSort();

    dp();
    
    for(int i=1; i<=N; ++i)
        if(out[i]==0&&res<f[i]) res = f[i];

    printf("%d\n", res);
}

int  main()
{
    while(scanf("%d%d", &N, &M)!=EOF)
    {
        init();
        solve();
    }
    return 0;
}

