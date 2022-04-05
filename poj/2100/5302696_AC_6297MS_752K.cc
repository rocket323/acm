#include <stdio.h>
#include <cmath>
#include <iostream>
using namespace std;
#define ll long long
#define INF 7e16

ll S[10][2], t[10], top, up, st;
ll n;

ll fun(ll x)
{
    double tmp = (double)x * (x + 1) * ((double)2*x + 1);
    if(tmp >= INF) return INF;
    return (ll)x * (x + 1) * ((ll)2*x + 1); 
}

ll cal(ll a, ll k)
{
    double tmp = (double)a * k * (a + k + 1) * 6 + (double)k * k * k * 2 + (double)k * k * 3 + k;
    if(tmp >= INF) return INF;
    ll ans = (ll)a * k * (a + k + 1) * 6 + (ll)k * k * k * 2 + (ll)k * k * 3 + k;
    return ans;
}

ll find(ll x, long long len)
{
    ll l = 0, r = n, mid;
    while(l <= r)
    {
        mid = (l + r) / 2;
        ll k = cal(mid, len);
        if(k==x) return mid;
        if(k > x) r = mid -1;
        else l = mid + 1;
    }
    return -1;
}

void go(long long len)
{
    long long k = (ll)n * 6;
    ll x = find(k, len);

    if(x != -1)
    {
        top++;
        S[top][0] = x + 1;
        S[top][1] = x + len;
    }
}

int main()
{

    while(scanf("%I64d", &n) != EOF)
    {
        up = pow(3*n, 1.0/3);
        up = (ll) up * 1.5;

        top = 0;
        for(int i=up; i>=1; --i) go(i);
        printf("%I64d\n", top);
        for(int i=1; i<=top; ++i)
        {
            printf("%I64d", S[i][1] - S[i][0] + 1);
            for(ll j=S[i][0]; j<=S[i][1]; ++j) printf(" %I64d", j);
            puts("");
        }
    }
    return 0;
}

