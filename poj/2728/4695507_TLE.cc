#include <iostream>
#include <cmath>
#define MaxN 1010
#define eps 1e-7
#define INF 1e10
#define ll long long
using namespace std;

ll x[MaxN], y[MaxN], z[MaxN], N;
double low[MaxN];
bool vis[MaxN];

void init()
{
    for(int i=0; i<N; ++i)
        scanf("%I64d%I64d%I64d", &x[i], &y[i], &z[i]);
}

double dist(int a, int b)
{
    return sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
}

double getLen(int a, int b, ll x)
{
    double k = fabs(z[a]-z[b])-x*dist(a, b);
    return k;
}

double check(double x)
{
    memset(vis, 0, sizeof vis);
    low[0] = 0;
    vis[0] = 1;
    for(int i=1; i<N; ++i)
    {
        low[i] = getLen(0, i, x);
    }

    double Min = INF, res = 0;
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
    double l = 0, r = INF, res = -1;
    while(l<=r+eps)
    {
        double mid = (l+r)/2.0;
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
    while(scanf("%I64d", &N), N!=0)
    {
        init();
        solve();
    }
    return 0;
}

