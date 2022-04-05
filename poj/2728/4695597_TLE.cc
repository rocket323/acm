#include <iostream>
#include <cmath>
#define MaxN 1010
#define eps 1e-7
#define ll long long
#define INF 1e20
using namespace std;

ll x[MaxN], y[MaxN], z[MaxN], N;
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
}

float getLen(ll a, ll b, ll x)
{
    return fabs(z[a]-z[b])-x*dist(a, b);
}

float check(float x)
{
    memset(vis, 0, sizeof vis);
    low[0] = 0;
    vis[0] = 1;
    for(ll i=1; i<N; ++i)
    {
        low[i] = getLen(0, i, x);
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
        for(ll i=1; i<N; ++i)
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
    float l = 0, r = 5, res = -1;
    while(l+eps<=r)
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
    while(scanf("%I64d", &N), N!=0)
    {
        init();
        solve();
    }
    return 0;
}

