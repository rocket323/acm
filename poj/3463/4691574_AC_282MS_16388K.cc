#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define MaxN 2001
#define ll long long
#define INF 2000000100
using namespace std;

struct Edge
{
    ll idx, w;
    Edge * next;
}adj[MaxN], memo[5*MaxN];

struct Hnode
{
    ll w, id;
    Hnode(ll x, ll y):id(x), w(y){}
};

struct cmp
{
    bool operator()(Hnode A, Hnode B){ return A.w>B.w; }
};

int g[MaxN][MaxN];
ll N, M, mset, S, T;
ll dist[MaxN], cnt0[MaxN], cnt1[MaxN];
ll Q[MaxN], top;
priority_queue<Hnode, vector<Hnode>, cmp> pq;

void addEdge(ll a, ll b, ll c)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->w = c;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void init()
{
    scanf("%I64d%I64d", &N, &M);
    mset = 0;
    for(ll i=0; i<=N; ++i) adj[i].next = NULL;

    memset(g, 0, sizeof g);
    for(ll i=0; i<M; ++i)
    {
        ll a, b, c;
        scanf("%I64d%I64d%I64d", &a, &b, &c);
        addEdge(a, b, c);
        if(c==1) g[a][b]++;
    }
    scanf("%I64d%I64d", &S, &T);
}

void dijkstra(ll src, ll T)
{

    memset(cnt0, 0, sizeof cnt0);
    memset(cnt1, 0, sizeof cnt1);
    cnt0[src] = 1;
    top = 0;

    for(ll i=1; i<=N; ++i) dist[i] = INF;
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
    for(ll i=0; i<top; ++i)
    {
        ll now = Q[i];
        Edge * ptr = adj[now].next;
        int x = i+1;
        while(x<top&&dist[Q[i]]==dist[Q[x]])
        {
            cnt1[now] += g[Q[x]][now]*cnt0[Q[x]];
            ++x;
        }

        while(ptr)
        {
            ll k = ptr->idx;
            if(dist[now]+ptr->w==dist[k]+1){ cnt1[k] += cnt0[now]; }
            if(cnt1[now]&&dist[now]+1+ptr->w==dist[k]+1){ cnt1[k] += cnt1[now]; }
            ptr = ptr->next;
        }
    }

    printf("%I64d\n", cnt0[T]+cnt1[T]);
}

void solve()
{
    dijkstra(S, T);
    process();
}

int main()
{
    ll T;
    scanf("%I64d", &T);
    while(T--)
    {
        init();
        solve();
    }
    return 0;
}

