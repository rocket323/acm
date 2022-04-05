#include <stdio.h>
#include <cstring>
#define maxl 60
#define sign(x) ((x)>0?(x):(-(x)))

int h[maxl], T[maxl][maxl], top[maxl], ts, n, ans, flag;

bool check(int t, int h)
{
    if(top[t] < 2) return 1;
    return (sign(T[t][top[t]-1] - T[t][top[t]-2]) == sign(h - T[t][top[t]-1]));
}

void dfs(int now, int dep)
{
    if(flag) return;
    if(now == n)
    {
        flag = 1;
        ans = ts;
        return;
    }

    for(int i=0; i<ts; ++i)
    {
        if(check(i, h[now]))
        {
            T[i][top[i]++] = h[now];
            dfs(now+1, dep);
            if(flag) return;
            top[i]--;
        }
    }

    if(ts < dep)
    {
        ts++;
        top[ts-1] = 1;
        T[ts-1][0] = h[now];
        dfs(now+1, dep);
        if(flag) return;
        ts--;
    }
}

void solve()
{
    for(int i=1; i<=n; ++i)
    {
        ans = n;
        flag = 0;
        ts = 0;
        dfs(0, i);
        if(flag)
        {
            printf("%d\n", i);
            return;
        }
    }
}

int main()
{
    while(scanf("%d", &n), n)
    {
        for(int i=0; i<n; ++i) scanf("%d", &h[i]);
        solve();
    }
    return 0;
}

