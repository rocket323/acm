#include <iostream>
#include <cmath>
using namespace std;
#define ll long long

ll N, a, b;

ll pp(ll x, ll num)
{
    ll res = 1;
    for(ll i=1; i<=num; ++i)
        res = (ll)res*x;
    return res;
}

bool check(ll b, ll p)
{
    for(ll i=b-50; i<=b+50; ++i)
        if(pp(i, p)==N)
            return 1;
    return 0;
}

void solve()
{
    int res = 1;
    for(int i=1; i<=36; ++i)
    {
        if(N<0&&i%2==0) continue;
        b = pow((double)N, 1.0/i);
        if(check(b, i))
            res = i;
    }
    printf("%d\n", res);
}

int main()
{
    while(scanf("%I64d", &N), N!=0)
    {
        solve();
    }
    return 0;
}

