#include <iostream>
#define MaxL 100000000
using namespace std;

int F, P, C, M;
int G[501][501], A[101];
int vis[501], dist[501];
int top, st[101];

void init()
{
    scanf("%d%d%d%d", &F, &P, &C, &M);
    for(int i=1; i<=F; ++i)
        for(int j=1; j<=F; ++j)
            G[i][j] = MaxL;
    for(int i=1; i<=P; ++i)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        G[a][b] = G[b][a] = c;
    }
    for(int i=1; i<=C; ++i)
        scanf("%d", &A[i]);
}

void dijstra()
{
    memset(vis, 0, sizeof vis);
    for(int i=1; i<=F; ++i)
        dist[i] = MaxL;
    dist[1] = 0;
    for(int i=1; i<=F; ++i)
    {
        int Min = MaxL, k = -1;
        for(int j=1; j<=F; ++j)
            if(!vis[j]&&dist[j]<Min)
            {
                Min = dist[j];
                k = j;
            }
        if(k==-1) return;
        vis[k] = 1;
        for(int j=1; j<=F; ++j)
            if(dist[k]+G[k][j]<dist[j])
                dist[j] = dist[k]+G[k][j];
    }
}

void process()
{
    dijstra();
    top = 0;
    for(int i=1; i<=C; ++i)
        if(dist[A[i]]<=M)
            st[++top] = i;
    printf("%d\n", top);
    for(int i=1; i<=top; ++i)
        printf("%d\n", st[i]);
}

int main()
{
    init();
    process();
    return 0;
}
