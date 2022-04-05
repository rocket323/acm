#include <stdio.h>
#include <cstring>
#define contain(n,x) (n & (1<<(x)))

int a, st, n;
short f[(1<<19)], ans[20], top;

int kip(int mask, int p)
{
    mask -= (1<<(p-2));
    for(int i=0; i<19; ++i)
    {
        if(!( (1<<i) & mask )) continue;
        int k = i + 2;
        if(k % p == 0) mask -= (1<<i);
        else if(k > p)
        {
            k -= p;
            for(int j=2; j<=k; ++j)
            {
                if(k % j) continue;
                if(!( (1<<(j-2)) & mask))
                {
                    mask -= (1 << (k + p - 2));
                    break;
                }
            }
        }
    }
    return mask;
}

short dp(int now)
{
    if(f[now] != -1) return f[now];

    for(int i=0; i<19; ++i)
    {
        if(!contain(now, i)) continue;

        int k = kip(now, i + 2);
        if(k < 0) printf("%d %d\n", now, i + 2);
        if(dp(k) == 0) return f[now] = 1;
    }
    return f[now] = 0;
}

void solve()
{
    memset(f, -1, sizeof f);
    f[0] = 0;

    top = 0;
    for(int i=0; i<19; ++i)
    {
        if(!( (1<<i) & st )) continue;

        int k = kip(st, i + 2);
        if(k < 0) printf("%d %d %d\n", st, i + 2, k);

        if(!dp(k)) ans[top++] = i + 2;
    }

    if(top == 0) puts("There's no winning move.");
    else
    {
        printf("The winning moves are:");
        for(int i=0; i<top; ++i) printf(" %d", ans[i]);
        puts("");
    }
    puts("");
}

int main()
{
    int tc = 0;
    while(scanf("%d", &n), n)
    {
        st = 0;
        for(int i=0; i<n; ++i)
        {
            scanf("%d", &a);
            st |= (1<<(a-2));
        }
        printf("Test Case #%d\n", ++tc);
        solve();
    }
    return 0;
}
