#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define MaxN 1001
#define INF 1000000100
using namespace std;

struct Edge
{
    int idx, w;
    Edge * next;
}adj[MaxN], memo[2*MaxN];

struct Hnode
{
    int w, id;
    Hnode(int x, int y):id(x), w(y){}
};

struct cmp
{
    bool operator()(Hnode A, Hnode B){ return A.w>B.w; }
};

int N, M, mset, S, T;
int dist[MaxN], cnt0[MaxN], cnt1[MaxN];
int Q[MaxN], top;
priority_queue<Hnode, vector<Hnode>, cmp> pq;

void addEdge(int a, int b, int c)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->w = c;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void init()
{
    scanf("%d%d", &N, &M);
    mset = 0;
    for(int i=0; i<=N; ++i) adj[i].next = NULL;

    for(int i=0; i<M; ++i)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        addEdge(a, b, c);
    }
    scanf("%d%d", &S, &T);
}

void dijkstra(int src, int T)
{

    memset(cnt0, 0, sizeof cnt0);
    memset(cnt1, 0, sizeof cnt1);
    cnt0[src] = 1;
    top = 0;

    for(int i=1; i<=N; ++i) dist[i] = INF;
    dist[src] = 0;
    pq.push(Hnode(src, 0));
    while(!pq.empty())
    {
        Hnode now = pq.top();
        pq.pop();
        if(now.w>dist[now.id]) continue;
        Q[top++] = now.id;
        Edge * ptr = adj[now.id].next;
        while(ptr)
        {
            if(dist[now.id]+ptr->w<dist[ptr->idx])
            {
                dist[ptr->idx] = dist[now.id] + ptr->w;
                pq.push(Hnode(ptr->idx, dist[ptr->idx]));
                cnt0[ptr->idx] = cnt0[now.id];
            }
            else if(dist[now.id]+ptr->w==dist[ptr->idx])
            {
                cnt0[ptr->idx] += cnt0[now.id];
            }
            ptr = ptr->next;
        }
    }
}

void process()
{
    for(int i=0; i<top; ++i)
    {
        int now = Q[i];
        Edge * ptr = adj[now].next;
        while(ptr)
        {
            int k = ptr->idx;
            if(dist[now]+ptr->w==dist[k]+1) cnt1[k] += cnt0[now];
            if(cnt1[now]&&dist[now]+1+ptr->w==dist[k]+1) cnt1[k] += cnt1[now];
            ptr = ptr->next;
        }
    }
    printf("%d\n", cnt0[T]+cnt1[T]);
}

void solve()
{
    dijkstra(S, T);
    process();
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

