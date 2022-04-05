#include <iostream>
#define MaxN 30010
#define INF 1000000000
using namespace std;

int N, d[MaxN];
int f[MaxN][4], g[MaxN][4];

void init()
{
    scanf("%d", &N);
    for(int i=1; i<=N; ++i)
        scanf("%d", &d[i]);
}

int Min(int a, int b){ return (a<b)?a:b; }

void solve()
{
    int res = INF;
    f[0][0] = g[0][3] = 0;
    f[0][1] = f[0][2] = INF;
    g[0][1] = g[0][2] = INF;
    for(int i=1; i<=N; ++i)
    {
        int w;
        for(int j=1; j<=3; ++j)
        {
            if(j==d[i]) w = 0;
            else w = 1;
            f[i][j] = g[i][j] = INF;
            for(int k=1; k<=3; ++k)
            {
                if(k<=j)
                    f[i][j] = Min(f[i][j], f[i-1][k]+w);
                if(k>=j)
                    g[i][j] = Min(g[i][j], g[i-1][k]+w);
            }
            if(i==N)
            {
                res = Min(res, f[i][j]);
                res = Min(res, g[i][j]);
            }
        }
    }
    printf("%d\n", res);
}

int main()
{
    init();
    solve();
    return 0;
}

