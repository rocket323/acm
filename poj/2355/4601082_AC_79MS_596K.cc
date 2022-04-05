#include <iostream>
#define MaxN 10010
#define INF 1000000010
using namespace std;

int l[4], c[4], S, T;
int N;
int f[MaxN], g[MaxN][4], P[MaxN];

int dist(int a, int b)
{
    return P[b] - P[a];
}

void init()
{
    for(int i=1; i<=3; ++i) scanf("%d", &l[i]);
    for(int i=1; i<=3; ++i) scanf("%d", &c[i]);
    scanf("%d", &N);
    scanf("%d%d", &S, &T);
    P[1] = 0;
    for(int i=2; i<=N; ++i)
        scanf("%d", &P[i]);
    if(S>T)
    {
        int tmp = S; S = T; T = tmp;
    }
}

void solve()
{
    int x;
    memset(g, -1, sizeof g);
    for(int i=1; i<=3; ++i)
    {
        x = S;
        for(int j=S+1; j<=T; ++j)
        {
            while( x<j && dist(x, j)>l[i]) ++x;
            g[j][i] = x;
        }
    }

    f[S] = 0;
    for(int i=S+1; i<=T; ++i)
    {
        f[i] = INF;
        for(int j=1; j<=3; ++j)
        {
            if(f[g[i][j]]+c[j]<f[i])
                f[i] = f[g[i][j]] + c[j];
        }
    }
    printf("%d\n", f[T]);
}

int main()
{
    init();
    solve();
    return 0;
}

