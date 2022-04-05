#include <iostream>
#include <cmath>
#define MaxN 1010
#define eps 1e-5
#define ll long long
#define INF 1e20
using namespace std;

ll x[MaxN], y[MaxN], z[MaxN], N;
ll cloest[MaxN];
float low[MaxN];
bool vis[MaxN];
//float g[MaxN][MaxN], h[MaxN][MaxN];

float dist(ll a, ll b)
{
    return sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
}

void init()
{
    for(ll i=0; i<N; ++i)
        scanf("%I64d%I64d%I64d", &x[i], &y[i], &z[i]);
    /*for(ll i=0; i<N; ++i)
        for(ll j=i; j<N; ++j)
        {
            g[i][j] = g[j][i] = dist(i, j);
            h[i][j] = h[j][i] = fabs(z[i]-z[j]);
        }*/
}

float getLen(ll a, ll b, ll x)
{
    return fabs(z[a]-z[b])-x*dist(a, b);
    //return h[a][b]-x*g[a][b];
}

float check(float x)
{
    memset(vis, 0, sizeof vis);
    low[0] = cloest[0] = 0;
    vis[0] = 1;

    float l1=0, l2=0;

    for(ll i=1; i<N; ++i)
    {
        low[i] = getLen(0, i, x);
        cloest[i] = 0;
    }

    float Min = INF, res = 0;
    for(ll p=1; p<N; ++p)
    {
        Min = INF;
        ll k = -1;
        for(ll i=1; i<N; ++i)
        {
            if(!vis[i]&&low[i]<Min)
            {
                Min = low[i];
                k = i;
            }
        }
        vis[k] = 1;
        res += Min;

        l1 += fabs(z[k]-z[cloest[k]]);
        l2 += dist(k, cloest[k]);
        //l1 += h[k][cloest[k]];
        //l2 += g[k][cloest[k]];

        for(ll i=1; i<N; ++i)
        {
            if(!vis[i]&&low[i]>=getLen(i, k, x))
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
    float l = 0, r = 31, res = -1;
    res = 31;
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
    while(scanf("%I64d", &N), N!=0)
    {
        init();
        solve();
    }
    return 0;
}

