#include <stdio.h>
#include <cmath>
#include <iostream>
using namespace std;
#define ll long long

int S[100][100], t[100], top, up, st;
ll n;

ll fun(int x){ return (ll)x * (x + 1) * (2*x + 1); }

int find(ll x, int len)
{
    int l = 0, r = st, mid;
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

void go(int len)
{
    long long k = (ll)n * 6;
    int x = find(k, len);
    if(x != -1)
    {
        top++;
        for(int j=x+1; j<=x+len; ++j) S[top][j-x] = j;
        t[top] = len;
    }
}

int main()
{
    while(cin >> n)
    {
        up = 0;
        while((ll)up * up <= n) up++;
        up += 10;
        st = sqrt(n) + 10;

        top = 0;
        for(int i=up; i>=1; --i) go(i);
        printf("%d\n", top);
        for(int i=1; i<=top; ++i)
        {
            printf("%d", t[i]);
            for(int j=1; j<=t[i]; ++j) printf(" %d", S[i][j]);
            puts("");
        }
    }
}

