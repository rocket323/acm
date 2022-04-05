#include <iostream>
#define UNVIS 0
#define VIS 1
#define OVER 2
#define MaxL 3030
using namespace std;

struct Edge
{
    int idx;
    Edge * next;
}
adj[MaxL], memo[40*MaxL];

int N, M, opp[MaxL];
int la[MaxL], lb[MaxL], mset;
int id[MaxL], low[MaxL], lt, mark[MaxL];
int pre[MaxL], S[MaxL], sz;

void addEdge(int a, int b)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void init()
{
    for(int i=1; i<=N; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        opp[a] = b;
        opp[b] = a;
    }
    for(int i=0; i<M; ++i) scanf("%d%d", &la[i], &lb[i]);
}

void dfs(int now)
{
    mark[now] = VIS;
    id[now] = low[now] = lt++;
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
    if(id[now]==low[now])
    {
        do
        {
            pre[S[sz]] = now;
            mark[S[sz]] = OVER;
        }while(S[sz--]!=now);
    }
}

bool check(int x)
{
    mset = 0;
    for(int i=0; i<2*N; ++i) adj[i].next = NULL;

    for(int i=0; i<x; ++i)
    {
        addEdge(opp[la[i]], lb[i]);
        addEdge(opp[lb[i]], la[i]);
    }

    for(int i=0; i<2*N; ++i) pre[i] = i;
    lt = sz = 0;
    memset(mark, 0, sizeof mark);
    for(int i=0; i<2*N; ++i)
        if(mark[i]==UNVIS) dfs(i);

    for(int i=0; i<2*N; ++i)
        if(pre[i] == pre[opp[i]]) return 0;

    return 1;
}

void solve()
{
    int l=0, r=M, mid, res = 0;
    while(l<=r)
    {
        mid = (l+r)>>1;
        if(check(mid))
        {
            res = mid;
            l = mid+1;
        }
        else r = mid-1;
    }
    printf("%d\n", res);
}

int main()
{
    while(scanf("%d%d", &N, &M) && N)
    {
        init();
        solve();
    }
    return 0;
}

