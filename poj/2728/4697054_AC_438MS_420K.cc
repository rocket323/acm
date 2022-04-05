#include <iostream>
#include <cmath>
#define MaxN 1010
#define eps 1e-5
#define INF 0xfffff
using namespace std;

int x[MaxN], y[MaxN], z[MaxN], N;
int cloest[MaxN];
double low[MaxN];
bool vis[MaxN];

double dist(int a, int b)
{
    return sqrt(double((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b])));
}

void init()
{
    for(int i=0; i<N; ++i)
        scanf("%d%d%d", &x[i], &y[i], &z[i]);
}

double getLen(int a, int b, double x)
{
    return abs(z[a]-z[b])-x*dist(a, b);
}

double check(double x)
{
    memset(vis, 0, sizeof vis);
    low[0] = cloest[0] = 0;
    vis[0] = 1;

    double l1=0, l2=0;

    for(int i=1; i<N; ++i)
    {
        low[i] = getLen(0, i, x);
        cloest[i] = 0;
    }

    double Min;
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

        l1 += abs(z[k]-z[cloest[k]]);
        l2 += dist(k, cloest[k]);

        for(int i=1; i<N; ++i)
        {
            if(!vis[i]&&low[i]>getLen(i, k, x))
            {
                low[i] = getLen(i, k, x);
                cloest[i] = k;
            }
        }
    }
    return (l1)/l2;
}

void solve()
{
    double l = 0, r = 20, res = -1;
    res = 0;
    double k;
    while(1)
    {
        k = check(res);
        if(fabs(k-res)<=1e-6) break;
        res = k;
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

