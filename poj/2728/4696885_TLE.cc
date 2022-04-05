#include <iostream>
#include <cmath>
#define MaxN 1010
#define eps 1e-5
//#define int long long
#define INF 10000000
using namespace std;

int x[MaxN], y[MaxN], z[MaxN], N;
int cloest[MaxN];
double low[MaxN];
bool vis[MaxN];
//double g[MaxN][MaxN], h[MaxN][MaxN];

double dist(int a, int b)
{
    return sqrt(double((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b])));
}

void init()
{
    for(int i=0; i<N; ++i)
        scanf("%d%d%d", &x[i], &y[i], &z[i]);
    /*for(int i=0; i<N; ++i)
        for(int j=i; j<N; ++j)
        {
            g[i][j] = g[j][i] = dist(i, j);
            h[i][j] = h[j][i] = fabs(z[i]-z[j]);
        }*/
}

double getLen(int a, int b, int x)
{
    return abs(z[a]-z[b])-x*dist(a, b);
    //return h[a][b]-x*g[a][b];
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
        l2 += Min;
        //l1 += h[k][cloest[k]];
        //l2 += g[k][cloest[k]];

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
        if(fabs(k-res)<=eps) break;
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

