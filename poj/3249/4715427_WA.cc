#include <iostream>
#define MaxN 100010
#define INF 2000000000
using namespace std;

struct Edge
{
    int idx;
    Edge * next;
};
Edge adj[MaxN], memo[10*MaxN];

int N, M, mset, C[MaxN];
int f[MaxN], Q[MaxN], head, tail;
int mark[MaxN], res;
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

void bfs(int s)
{
    head = tail = 1;
    Q[1] = s;
    f[s] = C[s];
    mark[s] = 1;
    while(head<=tail)
    {
        Edge * ptr = adj[Q[head]].next;
        while(ptr)
        {
            int k = ptr->idx;
            if(f[k]<f[Q[head]]+C[k]) f[k] = f[Q[head]] + C[k];
            if(!mark[k])
            {
                mark[k] = 1;
                Q[++tail] = k;
            }
            ptr = ptr->next;
        }
        head++;
    }
}

void solve()
{
    res = -INF;
    memset(mark, 0, sizeof mark);

    for(int i=1; i<=N; ++i) f[i] = -INF;

    for(int i=1; i<=N; ++i)
        if(!mark[i]&&in[i]==0)
        {
            bfs(i);
        }
    
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

