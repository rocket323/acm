#include <iostream>
#define MaxN 6000
#define MaxE 30000
using namespace std;

struct Edge
{
    int idx;
    Edge * next;
};
Edge adj[MaxN], memo[40010];

int N, M, mset, res, pre[MaxN];
int id[MaxN], low[MaxN], lv;
int bridge[MaxE][2], sz;
int mark[MaxN], d[MaxN];

void addEdge(int a, int idx)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = idx;
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
        int a, b;
        scanf("%d%d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    res = 0;
    for(int i=0; i<=N; ++i) pre[i] = i;
}

int find(int x)
{
    if(pre[x]==x) return x;
    return pre[x] = find(pre[x]);
}

void unionSet(int a, int b)
{
    int x = find(a), y = find(b);
    if(x!=y) pre[x] = y;
}

void visit(int now, int father)
{
    id[now] = low[now] = lv++;
    mark[now] = 1;

    for(Edge* ptr = adj[now].next; ptr!=NULL; ptr = ptr->next)
    {
        int k = ptr->idx;
        if(!mark[k])
        {
            visit(k, now);
            if(low[k]<low[now]) low[now] = low[k];
            if(low[k]<=id[now]) unionSet(now, k);
            if(low[k]>id[now])
            {
                bridge[sz][0] = now;
                bridge[sz++][1] = k;
            }
        }
        else if(k!=father)
        {
            if(low[k]<low[now]) low[now] = low[k];
        }
    }
}

void solve()
{
    memset(mark, 0, sizeof mark);
    lv = sz = 0;
    visit(1, -1);
    
    memset(d, 0, sizeof d);
    for(int i=0; i<sz; ++i)
    {
        int a = find(bridge[i][0]);
        int b = find(bridge[i][1]);
        d[a]++;
        d[b]++;
    }

    for(int i=1; i<=N; ++i) if(d[i]==1) res++;

    printf("%d\n", (res+1)/2);
}
int main()
{
    init();
    solve();
    return 0;
}

