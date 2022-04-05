#include <stdio.h>
#include <cstring>
#define maxl 60
#define sign(x) ((x)>0?1:(-1))
#define min(a,b) ((a<b)?a:b)
#define INF 0x3f3f3f3f

int a[maxl], T[maxl][maxl], top[maxl], ts, n, ans, flag;
int up[maxl];

void dfs(int now)
{
    if(ts >= ans) return;
    if(now == n)
    {
        ans = ts;
        return;
    }

    int l = INF, h = -INF, lr = -1, hr = -1;

    for(int i=0; i<ts; ++i)
    {
        int k = T[i][top[i]-1];
        if(up[i] >= 0 && k < a[now] && k > h)
        {
            h = k;
            hr = i;
        }
        if(up[i] <= 0 && k > a[now] && k < l)
        {
            l = k;
            lr = i;
        }
    }

    if(hr != -1)
    {
        int sv = up[hr];

        if(a[now] > T[hr][top[hr]-1]) up[hr] = 1;
        else up[hr] = -1;

        T[hr][top[hr]] = a[now];
        top[hr]++;
        dfs(now+1);
        top[hr]--;
        up[hr] = sv;
    }

    if(lr != -1)
    {
        int sv = up[lr];

        if(a[now] > T[lr][top[lr]-1]) up[lr] = 1;
        else up[lr] = -1;
        
        T[lr][top[lr]] = a[now];
        top[lr]++;
        dfs(now+1);
        top[lr]--;
        up[lr] = sv;
    }

    if(ts < ans - 1)
    {
        ts++;
        top[ts-1] = 1;
        up[ts-1] = 0;
        T[ts-1][0] = a[now];
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
        for(int i=0; i<n; ++i) scanf("%d", &a[i]);
        solve();
    }
    return 0;
}

