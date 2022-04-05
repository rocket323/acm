#include <iostream>
#include <algorithm>
#define MaxN 200010
using namespace std;

struct Edge
{
    int a, b, c;
}E[MaxN];

bool cmp(Edge A, Edge B){ return A.c<B.c; }

bool vis[MaxN];
int N, M, pre[101];

void init()
{
    scanf("%d%d", &N, &M);
    for(int i=1; i<=M; ++i)
    {
        scanf("%d%d%d", &E[i].a, &E[i].b, &E[i].c);
    }
    sort(E+1, E+M+1, cmp);
}

int find(int x)
{
    if(pre[x]==x) return x;
    int ans = find(pre[x]);
    pre[x] = ans;
    return ans;
}

int kruskal()
{
    for(int i=1; i<=N; ++i) pre[i] = i;
    int cnt = 0, res = 0;
    for(int i=1; i<=M; ++i)
    {
        int x = find(E[i].a);
        int y = find(E[i].b);
        if(x==y) continue;
        ++cnt; vis[i] = 1; res += E[i].c;
        if(cnt==N-1) return res;
        pre[x] = y;
    }
    return -1;
}

void solve()
{
    memset(vis, 0, sizeof vis);
    int k = kruskal();
    if(N==1&&M==0){ printf("0\n"); return; }
    for(int i=2; i<=M; ++i)
    {
        if(E[i].c==E[i-1].c&&vis[i]!=vis[i-1])
        {
            printf("Not Unique!\n");
            return;
        }
    }
    printf("%d\n", k);
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

