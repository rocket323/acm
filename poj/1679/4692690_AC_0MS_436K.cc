#include <iostream>
#include <algorithm>
#define INF 1000000000
using namespace std;

int N, M, pre[101];
int g[101][101], cnt[101];
int f[101][101], low[101], cloest[101];
int vis[101];

void init()
{
    scanf("%d%d", &N, &M);
    int a, b, c;
    for(int i=1; i<=N; ++i)
        for(int j=1; j<=N; ++j)
            g[i][j] = INF;
    for(int i=1; i<=M; ++i)
    {
        scanf("%d%d%d", &a, &b, &c);
        if(g[a][b]==-1||c<g[a][b])
        {
            g[a][b] = g[b][a] = c;
        }
    }
}

int Max(int a, int b){ return (a>b)?a:b; }

void prim()
{
    int Min, res = 0;
    memset(vis, 0, sizeof vis);
    vis[1] = 1; cloest[1] = 0;

    for(int i=2; i<=N; ++i)
    {
        cloest[i] = 1;
        low[i] = g[i][1];
    }

    memset(f, 0, sizeof f);
    for(int x=1; x<N; ++x)
    {
        Min = INF;
        int k = -1;
        for(int i=2; i<=N; ++i)
            if(!vis[i]&&low[i]<Min)
            {
                k = i;
                Min = low[i];
            }
        for(int i=1; i<=N; ++i)
            if(vis[i])
            {
                f[k][i] = f[i][k] = Max(f[i][cloest[k]], low[k]);
            }
        vis[k] = 1;
        res += low[k];
        for(int i=1; i<=N; ++i)
            if(!vis[i])
            {
                if(g[i][k]<=low[i])
                {
                    low[i] = g[i][k];
                    cloest[i] = k;
                }
            }
    }
    for(int i=1; i<=N; ++i)
        for(int j=1; j<=N; ++j)
        {
            if(i==j) continue;
            if(cloest[i]==j||cloest[j]==i) continue;
            if(f[i][j]==g[i][j])
            {
                printf("Not Unique!\n");
                return;
            }
        }
    printf("%d\n", res);
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        init();
        prim();
    }
    return 0;
}

