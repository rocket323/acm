#include <stdio.h>
#include <cstring>
#define MaxL 100010
#define INF 0xfffffffffffffffLL

int n, h[MaxL], l[MaxL], r[MaxL], S[MaxL], top;

void solve()
{
    S[top = 1] = 0;
    h[0] = -1;
    for(int i=1; i<=n; ++i)
    {
        while(h[S[top]]>=h[i]) top--;
        l[i] = S[top];
        S[++top] = i;
    }
    S[top = 1] = n + 1;
    h[n + 1] = -1;
    for(int i=n; i>=1; --i)
    {
        while(h[S[top]]>=h[i]) top--;
        r[i] = S[top];
        S[++top] = i;
    }
    long long ans = -INF;
    for(int i=1; i<=n; ++i)
    {
        long long k = (long long)h[i] * (r[i] - l[i] -1);
        if(k > ans) ans = k;
    }
    printf("%I64d\n", ans);
}

int main()
{
    while(scanf("%d", &n) && n)
    {
        for(int i=1; i<=n; ++i) scanf("%d", &h[i]);
        solve();
    }
    return 0;
}

