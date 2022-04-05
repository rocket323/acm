#include <iostream>
#include <algorithm>
#define INF 1000000000
using namespace std;

struct Edge
{
    int a, b, c;
}E[10010];

int N, M, pre[101];

bool cmp(Edge A, Edge B){ return A.c<B.c; }

void init()
{
    for(int i=0; i<M; ++i)
        scanf("%d%d%d", &E[i].a, &E[i].b, &E[i].c);
    sort(E, E+M, cmp);
}

int find(int x)
{
    if(x==pre[x]) return x;
    return pre[x] = find(pre[x]);
}

int kruskal(int s)
{
    for(int i=1; i<=N; ++i) pre[i] = i;
    int cnt = 0;
    for(int i=s; i<M; ++i)
    {
        int x = find(E[i].a);
        int y = find(E[i].b);
        if(x==y) continue;
        ++cnt;
        if(cnt==N-1) return E[i].c;
        pre[x] = y;
    }
    return -1;
}

int Min(int a, int b){ return (a<b)?a:b; }

void solve()
{
    int res = INF;
    for(int i=0; i<M; ++i)
    {
        int k = kruskal(i);
        if(k!=-1)
        {
            res = Min(res, k-E[i].c);
        }
    }
    if(res==INF) printf("-1\n");
    else printf("%d\n", res);
}

int main()
{
    while(scanf("%d%d", &N, &M), N!=0)
    {
        init();
        solve();
    }
    return 0;
}

