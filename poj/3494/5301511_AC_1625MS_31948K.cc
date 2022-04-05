#include <stdio.h>
#include <cstring>
#define MaxL 2009
#define INF 0x7f7f7f7f

int A[MaxL][MaxL], n, m;
int h[MaxL][MaxL];
int S[MaxL], top, l[MaxL], r[MaxL];

void init()
{
    for(int i=1; i<=n; ++i)
    {
        for(int j=1; j<=m; ++j) scanf("%d", &A[i][j]);
    }
    for(int j=1; j<=m; ++j)
    {
        h[0][j] = 0;
        for(int i=1; i<=n; ++i)
        {
            if(A[i][j]==0) h[i][j] = 0;
            else h[i][j] = h[i-1][j] + 1;
        }
    }
}

int go(int now)
{
    S[top = 1] = 0;
    h[now][0] = -1;
    for(int i=1; i<=m; ++i)
    {
        while(h[now][S[top]] >= h[now][i]) top--;
        l[i] = S[top];
        S[++top] = i;
    }
    S[top = 1] = m + 1;
    h[now][m + 1] = -1;
    for(int i=m; i>=1; --i)
    {
        while(h[now][S[top]] >= h[now][i]) top--;
        r[i] = S[top];
        S[++top] = i;
    }
    int ans = -INF;
    for(int i=1; i<=m; ++i)
    {
        int k = h[now][i] * (r[i] - l[i] - 1);
        if(k > ans) ans = k;
    }
    return ans;
}

void solve()
{
    int ans = -INF;
    for(int i=1; i<=n; ++i)
    {
        int k = go(i);
        if(k > ans) ans = k;
    }
    printf("%d\n", ans);
}

int main()
{
    while(scanf("%d%d", &n, &m)!=EOF)
    {
        init();
        solve();
    }
    return 0;
}

