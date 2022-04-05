#include <stdio.h>
#include <cstring>
#define maxl 50

int f[maxl][200], d[maxl], t[maxl], sum, n, w[maxl], h;
int p[maxl][200], C[maxl][200];

int max(int a, int b){ return (a > b) ? a : b; }

void init()
{
    scanf("%d", &h);
    for(int i=0; i<n; ++i) scanf("%d", &w[i]);
    for(int i=0; i<n; ++i) scanf("%d", &d[i]);
    for(int i=0; i<n-1; ++i) scanf("%d", &t[i]);
    t[n-1] = 0;
    sum = h * 12;
}

inline int calc(int a, int d, int n)
{
    int k;
    if(d != 0) k = (a + d) / d;
    else k = 100000;
    if(k < n) n = k;
    return n * a - n * (n - 1) / 2 * d;
}

void solve()
{
    memset(f, 0, sizeof f);
    memset(p, 0, sizeof p);

    for(int i=0; i<n; ++i)
        for(int j=0; j<=sum; ++j)
            C[i][j] = calc(w[i], d[i], j);

    for(int i=n-1; i>=0; --i)
    {
        for(int j=1; j<=sum; ++j)
        {
            for(int k=0; k+t[i]<j; ++k)
            {
                int tmp = f[i+1][j-t[i]-k] + C[i][k];
                if(tmp >= f[i][j])
                {
                    f[i][j] = tmp;
                    p[i][j] = j - t[i] - k;
                }
            }
            int tmp = f[i+1][0] + C[i][j];
            if(tmp >= f[i][j])
            {
                f[i][j] = tmp;
                p[i][j] = 0;
            }
        }
    }

    int now = sum;
    for(int i=0; i<n-1; ++i)
    {
        int a;
        if(p[i][now] != 0) a = 5 * (now - p[i][now] - t[i]);
        else a = 5 * (now - p[i][now]);
        printf("%d, ", a);
        now = p[i][now];
    }

    printf("%d\n", now * 5);

    printf("Number of fish expected: %d\n", f[0][sum]);
}

int main()
{
    int t = 0;
    while(scanf("%d", &n), n)
    {
        init();
        solve();
        puts("");
    }
    return 0;
}

