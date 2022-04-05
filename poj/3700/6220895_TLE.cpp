#include <stdio.h>
#include <cstring>
#define maxl 60
#define sign(x) ((x)>0?1:(-1))
#define min(a,b) ((a<b)?a:b)

int h[maxl], T[maxl][maxl], top[maxl], ts, n, ans, flag;

inline bool check(int t, int h)
{
    if(top[t] < 2) return 1;
    int t1 = sign(T[t][top[t]-1] - T[t][top[t]-2]), t2 = sign(h - T[t][top[t]-1]); 
    if(t2 == 0) return 0;
    return t1 == t2;
}

void dfs(int now)
{
    if(ts >= ans) return;
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
            dfs(now+1);
            top[i]--;
        }
    }

    if(ts < ans)
    {
        ts++;
        top[ts-1] = 1;
        T[ts-1][0] = h[now];
        dfs(now+1);
        ts--;
    }
}

void solve()
{
    memset(top, 0, sizeof top);
    ans = min(8, n);
    //for(int i=1; i<=n; ++i)
    //{
        flag = 0;
        ts = 0;
        dfs(0);

        printf("%d\n", ans);

        /*
        if(flag)
        {
            printf("%d\n", i);
            return;
        }
        */
    //}
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

