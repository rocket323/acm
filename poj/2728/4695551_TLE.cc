#include <iostream>
#include <cmath>
#define MaxN 1010
#define eps 1e-7
#define INF 1000000000
using namespace std;

int x[MaxN], y[MaxN], z[MaxN], N;
float low[MaxN];
bool vis[MaxN];
float g[MaxN][MaxN], h[MaxN][MaxN];

float dist(int a, int b)
{
    return sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
}

void init()
{
    for(int i=0; i<N; ++i)
        scanf("%d%d%d", &x[i], &y[i], &z[i]);
    for(int i=0; i<N; ++i)
        for(int j=i; j<N; ++j)
        {
            g[i][j] = g[j][i] = dist(i, j);
            h[i][j] = h[j][i] = fabs(z[i]-z[j]);
        }
}

float getLen(int a, int b, int x)
{
    return h[a][b]-x*g[a][b];
}

float check(float x)
{
    memset(vis, 0, sizeof vis);
    low[0] = 0;
    vis[0] = 1;
    for(int i=1; i<N; ++i)
    {
        low[i] = getLen(0, i, x);
    }

    float Min = INF, res = 0;
    for(int p=1; p<N; ++p)
    {
        Min = INF;
        int k = -1;
        for(int i=1; i<N; ++i)
        {
            if(!vis[i]&&low[i]<Min)
            {
                Min = low[i];
                k = i;
            }
        }
        vis[k] = 1;
        res += Min;
        for(int i=1; i<N; ++i)
        {
            if(!vis[i]&&low[i]>=getLen(i, k, x))
            {
                low[i] = getLen(i, k, x);
            }
        }
    }
    return res;
}

void solve()
{
    float l = 0, r = INF, res = -1;
    while(l<=r+eps)
    {
        float mid = (l+r)/2.0;
        if(check(mid)<=0)
        {
            res = mid;
            r = mid-eps;
        }
        else l = mid + eps;
    }
    printf("%.3f\n", res);
}

int main()
{
    while(scanf("%d", &N), N!=0)
    {
        init();
        solve();
    }
    return 0;
}
