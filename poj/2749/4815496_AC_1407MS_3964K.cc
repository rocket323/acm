#include <iostream>
#include <cmath>
#define MaxL 2010
#define INF 4000010
#define UNVIS 0
#define VIS 1
#define OVER 2
using namespace std;

struct Edge
{
    int idx;
    Edge * next;
}
adj[MaxL], memo[1000*MaxL];

int N, A, B;
int sx1, sy1, sx2, sy2, mset;
int x[MaxL], y[MaxL];
int ha[MaxL], hb[MaxL];
int la[MaxL], lb[MaxL];
int id[MaxL], low[MaxL], lt, S[MaxL], sz;
int mark[MaxL], pre[MaxL];

int dist(int x1, int y1, int x2, int y2)
{
    return abs(x1-x2) + abs(y1-y2);
}

int opp(int x){ return (x<N)? x+N : x-N; }

void addEdge(int a, int b)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void init()
{
    scanf("%d%d%d%d", &sx1, &sy1, &sx2, &sy2);
    for(int i=0; i<N; ++i) scanf("%d%d", &x[i], &y[i]);
    for(int i=0; i<A; ++i){ scanf("%d%d", &ha[i], &hb[i]); ha[i]--; hb[i]--; }
    for(int i=0; i<B; ++i){ scanf("%d%d", &la[i], &lb[i]); la[i]--; lb[i]--; }
}

void dfs(int now)
{
    mark[now] = VIS;
    low[now] = id[now] = lt++;
    S[++sz] = now;

    Edge * ptr = adj[now].next;
    while(ptr)
    {
        int k = ptr->idx;
        if(mark[k]==UNVIS)
        {
            dfs(k);
            if(low[k]<low[now]) low[now] = low[k];
        }
        else if(mark[k]==VIS)
        {
            if(low[k]<low[now]) low[now] = low[k];
        }
        ptr = ptr->next;
    }
    if(low[now]==id[now])
    {
        do
        {
            pre[S[sz]] = now;
            mark[S[sz]] = OVER;
        }
        while(S[sz--]!=now);
    }
}

bool check(int LIM)
{
    mset = 0;
    for(int i=0; i<2*N; ++i) adj[i].next = NULL;

    /*for(int i=0; i<N; ++i)
    {
        if(dist(x[i], y[i], sx1, sy1)>LIM) addEdge(i, i+N);
        if(dist(x[i], y[i], sx2, sy2)>LIM) addEdge(i+N, i);
    }*/

    for(int i=0; i<N; ++i)
    {
        for(int j=i+1; j<N; ++j)
        {
            if(i==j) continue;
            if(dist(x[i], y[i], sx1, sy1) + dist(x[j], y[j], sx1, sy1) > LIM)
            {
                addEdge(i, opp(j));
                addEdge(j, opp(i));
            }
            if(dist(x[i], y[i], sx2, sy2) + dist(x[j], y[j], sx2, sy2) > LIM)
            {
                addEdge(opp(i), j);
                addEdge(opp(j), i);
            }
            if(dist(x[i], y[i], sx1, sy1) + dist(x[j], y[j], sx2, sy2) + dist(sx1, sy1, sx2, sy2) > LIM)
            {
                addEdge(i, j);
                addEdge(opp(j), opp(i));
            }
            if(dist(x[i], y[i], sx2, sy2) + dist(x[j], y[j], sx1, sy1) + dist(sx1, sy1, sx2, sy2) > LIM)
            {
                addEdge(opp(i), opp(j));
                addEdge(j, i);
            }
        }
    }

    for(int i=0; i<A; ++i)
    {
        addEdge(ha[i], opp(hb[i]));
        addEdge(hb[i], opp(ha[i]));
        addEdge(opp(ha[i]), hb[i]);
        addEdge(opp(hb[i]), ha[i]);
    }
    for(int i=0; i<B; ++i)
    {
        addEdge(la[i], lb[i]);
        addEdge(lb[i], la[i]);
        addEdge(opp(la[i]), opp(lb[i]));
        addEdge(opp(lb[i]), opp(la[i]));
    }

    memset(mark, 0, sizeof mark);
    lt = sz = 0;
    for(int i=0; i<2*N; ++i)
        if(mark[i]==UNVIS) dfs(i);

    for(int i=0; i<N; ++i)
        if(pre[i]==pre[i+N]) return 0;
    return 1;
}

void solve()
{
    int l = 0, r = INF, mid, res = -1;
    while(l<=r)
    {
        mid = (l+r)>>1;
        if(check(mid))
        {
            res = mid;
            r = mid-1;
        }
        else l = mid+1;
    }
    printf("%d\n", res);
}

int main()
{
    while(scanf("%d%d%d", &N, &A, &B)!=EOF)
    {
        init();
        solve();
    }
    return 0;
}

