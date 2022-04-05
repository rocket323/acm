#include <stdio.h>
#include <cmath>
#include <iostream>
using namespace std;
#define ll long long

ll S[100][5000], t[1000], top, up, st;
ll n;

ll fun(ll x){ return (ll)x * (x + 1) * ((ll)2*x + 1); }

ll find(ll x, long long len)
{
    ll l = 0, r = n, mid;
    while(l <= r)
    {
        mid = (l + r) / 2;
        ll k = fun(mid + len) - fun(mid);
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
        for(ll j=x+1; j<=x+len; ++j) S[top][j-x] = j;
        t[top] = len;
    }
}

int main()
{
    while(cin >> n)
    {
        up = 0;
        while((ll)up * up * up <= (ll)n * 6) up++;
        up += 100;
        st = (long long)sqrt(n * 1.0) + 100;

        top = 0;
        for(int i=up; i>=1; --i) go(i);
        printf("%I64d\n", top);
        for(ll i=1; i<=top; ++i)
        {
            printf("%I64d", t[i]);
            for(ll j=1; j<=t[i]; ++j) printf(" %I64d", S[i][j]);
            puts("");
        }
    }
    return 0;
}

