#include <stdio.h>
#include <cmath>
#include <iostream>
using namespace std;
#define ll long long
#define INF 7e16

ll S[1000][2], t[1000], top, up, st;
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
        //ll k = fun(mid + len);
        //if(k < INF) k -= fun(mid);
        ll k = cal(mid, len);
        /*if(len==10000)
        {
            cout<<mid<<' '<<k<<' '<<x<<endl;
        }*/
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

    //cout<< fun(100000) / 6 <<endl;

    while(cin >> n)
    {
        up = 0;
        while((ll)up * (ll)up * (ll)up <= (ll)n * 6) up++;
        up = (ll)up * 2;
        st = (long long)sqrt(n * 1.0) + 100;

        top = 0;
        for(ll i=up; i>=1; --i) go(i);
        printf("%I64d\n", top);
        for(ll i=1; i<=top; ++i)
        {
            printf("%I64d", S[i][1] - S[i][0] + 1);
            for(ll j=S[i][0]; j<=S[i][1]; ++j) printf(" %I64d", j);
            puts("");
        }
    }
    return 0;
}

