#include <iostream>
#include <cmath>
#define Size 301
#define INF 1000000000
using namespace std;

struct Edge
{
    int idx, f, w;
    Edge* next;
    Edge* opp;
};

Edge adj[Size], memo[60*Size];

int R, C, N, M, S, T;
char g[Size][Size];
int mr[Size], mc[Size], hr[Size], hc[Size];
int m, h, mset, ans;
int dist[Size];
Edge * pre[Size];

void addEdge(int a, int b, int c, int w)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->f = c;
    ptr->w = w;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void addEdgeProcess(int a, int b, int c, int w)
{
    addEdge(a, b, c, w);
    addEdge(b, a, 0, -w);
    adj[a].next->opp = &memo[mset-1];
    adj[b].next->opp = &memo[mset-2];
}

void init()
{
    mset = 0;
    N = 0; m = h = 0;
    char ch;
    for(int i=0; i<=T; ++i) adj[i].next = NULL;
    for(int i=1; i<=R; ++i)
    {
        for(int j=1; j<=C; ++j)
        {
            cin>>g[i][j];
            if(g[i][j]=='H')
            {
                ++N; ++h;
                hr[h] = i; hc[h] = j;
            }
            if(g[i][j]=='m')
            {
                ++m;
                mr[m] = i; mc[m] = j;
            }
        }
    }
    S = 2*N+1; T = S+1;
    for(int i=1; i<=m; ++i)
    {
        for(int j=1; j<=h; ++j)
            addEdgeProcess(i, j+N, 1, abs(mr[i]-hr[j])+abs(mc[i]-hc[j]));
        addEdgeProcess(S, i, 1, 0);
        addEdgeProcess(i+N, T, 1, 0);
    }
    for(int i=0; i<=T; ++i) pre[i] = NULL;
}

bool bellman_ford()
{
    for(int i=1; i<=T; ++i) dist[i] = INF;
    dist[S] = 0;
    for(int x=1; x<T; ++x)
    {
        for(int i=1; i<=T; ++i)
        {
            Edge * ptr = adj[i].next;
            while(ptr)
            {
                if(ptr->f<=0){ ptr = ptr->next; continue; }
                int k = ptr->idx;
                if(dist[i]+ptr->w<dist[k])
                {
                    dist[k] = dist[i] + ptr->w;
                    pre[k] = ptr;
                }
                ptr = ptr->next;
            }
        }
    }

    for(int i=1; i<=T; ++i)
    {
        Edge * ptr = adj[i].next;
        while(ptr)
        {
            if(ptr->f>0&&dist[i]+ptr->w<dist[ptr->idx])
                return 0;
            ptr = ptr->next;
        }
    }

    return (dist[T]<INF);
}

void add_Path()
{
    int k = T, Min = INF;
    Edge * ptr;
    while(k!=S)
    {
        ptr = pre[k];
        if(ptr->f<Min) Min = ptr->f;
        k = ptr->opp->idx;
    }
    k = T;
    while(k!=S)
    {
        ptr = pre[k];
        ptr->f -= Min;
        ptr->opp->f += Min;
        k = ptr->opp->idx;
    }
    ans += Min*dist[T];
}

void solve()
{
    ans = 0;
    while(bellman_ford())
    {
        add_Path();
    }
    printf("%d\n", ans);
}

int main()
{
    while(cin>>R>>C, R!=0)
    {
        init();
        solve();
    }
    return 0;
}

