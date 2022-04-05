#include <stdio.h>
#include <cstring>
#define ll long long

int n;
ll ans, f[30];

int euler(int n)
{
    int ans = n;
    for(int i=2; i*i<=n; ++i)
    {
        if(n % i) continue;
        ans = ans / i * (i - 1);
        while(n % i == 0) n /= i;
    }
    if(n > 1) ans = ans / n * (n - 1);
    return ans;
}

void go(int d)
{
    ans += euler(d) * f[n/d];
}

void solve()
{

    if(n==0)
    {
        printf("0\n");
        return;
    }

    ans = 0;
    for(int i=1; i*i<=n; ++i)
    {
        if(n % i) continue;
        go(i);
        if(i * i != n) go(n / i);
    }
    if(n & 1)
    {
        ans += n * f[(n+1)/2];
    }
    else
    {
        ans += ( n/2 * f[n/2] + n/2 * f[(n+2)/2] );
    }
    ans /= (2 * n);
    printf("%I64d\n", ans);
}

int main()
{
    f[0] = 1;
    for(int i=1; i<=25; ++i) f[i] = (ll)f[i-1] * 3;

    while(scanf("%d", &n), n!=-1)
    {
        solve();
    }
    return 0;
}
