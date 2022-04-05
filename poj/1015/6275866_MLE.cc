#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#define max(a,b) ((a>b)?a:b)
#define ADD 4000

short f[210][21][8010], sa[210], sb[210];
short ans_dif, ans_sum, n, m, a[210], b[210], ans[210], top;
short pa[210][21][8010];
bool vis[210];

void solve()
{
    sa[0] = sb[0] = 0;
    for(int i=1; i<=n; ++i)
    {
        scanf("%d%d", &a[i], &b[i]);
        sa[i] = sa[i-1] + a[i];
        sb[i] = sb[i-1] + b[i];
    }

    memset(f, -1, sizeof f);
    f[0][0][0 + ADD] = 0;

    ans_dif = 30000;
    ans_sum = -1;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<=m; ++j)
        {
            for(int k=ADD-sb[i]; k<=ADD+sa[i]; ++k)
            {
                if(f[i][j][k] == -1) continue;

                if(f[i][j][k] > f[i+1][j][k])
                {
                    f[i+1][j][k] = f[i][j][k];
                    pa[i+1][j][k] = j;
                }

                if(j < m && f[i][j][k] + a[i+1] + b[i+1] > f[i+1][j+1][k+a[i+1]-b[i+1]])
                {
                    f[i+1][j+1][k+a[i+1]-b[i+1]] = f[i][j][k] + a[i+1] + b[i+1];
                    pa[i+1][j+1][k+a[i+1]-b[i+1]] = j;
                }
            }
        }
    }

    for(int i=-max(sa[n], sb[n]); i<=max(sa[n], sb[n]); ++i)
    {
        if(f[n][m][i+ADD] == -1) continue;
        if(abs(i) < abs(ans_dif))
        {
            ans_dif = i;
            ans_sum = f[n][m][i+ADD];
        }
        else if(abs(i) == abs(ans_dif) && f[n][m][i+ADD] > ans_sum)
        {
            ans_dif = i;
            ans_sum = f[n][m][i+ADD];
        }
    }

    short na = (ans_dif + ans_sum) / 2, nb = (ans_sum - ans_dif) / 2, nc = m, n_dif = ans_dif;

    printf("Best jury has value %d for prosecution and value %d for defence:\n", na, nb);

    memset(vis, 0, sizeof vis);
    //printf("%d %d %d %d\n", n, m, n_dif, pa[n][m][n_dif+ADD]);
    for(int i=n; i>=1; --i)
    {
        if(pa[i][nc][n_dif+ADD] == nc - 1)
        {
            //printf("no %d %d %d %d\n", i, nc, n_dif, pa[i][nc][n_dif+ADD]);
            ans[top++] = i;
            n_dif = n_dif - a[i] + b[i];
            nc--;
            //printf("%d %d\n", nc, n_dif);
        }
    }

    for(int i=top-1; i>=0; --i) printf(" %d", ans[i]);
}

int main()
{
    int tc = 0;
    while(scanf("%d%d", &n, &m), n)
    {
        printf("Jury #%d\n", ++tc);
        solve();
        puts("");
    }
    return 0;
}

