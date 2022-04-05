#include <stdio.h>
#include <cstring>
#define maxl 60
#define sign(x) ((x)>0?1:(-1))
#define min(a,b) ((a<b)?a:b)

int h[maxl], T[maxl][maxl], top[maxl], ts, n, ans, flag;
int up[maxl];

void dfs(int now)
{
    if(ts >= ans) return;
    if(now == n)
    {
        ans = ts;
        return;
    }

    for(int i=0; i<ts; ++i)
    {
        int k = sign(h[now] - T[i][top[i]-1]), f = 0;
        if(up[i] == 0 || k == up[i])
        {
            if(up[i] == 0) up[i] = k, f = 1;
            T[i][top[i]++] = h[now];
            dfs(now+1);

            if(f) up[i] = 0;

            top[i]--;
        }
    }

    if(ts < ans - 1)
    {
        ts++;
        top[ts-1] = 1;
        up[ts-1] = 0;
        T[ts-1][0] = h[now];
        dfs(now+1);
        ts--;
    }
}

void solve()
{
    memset(top, 0, sizeof top);
    memset(up, 0, sizeof up);

    ans = min(8, n);
    ts = 0;
    dfs(0);

    printf("%d\n", ans);

}

int main()
{
    while(scanf("%d", &n) && (n>=1 && n<=50))
    {
        for(int i=0; i<n; ++i) scanf("%d", &h[i]);
        solve();
    }
    return 0;
}

