#include <stdio.h>
#include <cstring>

int n, cnt[101];

int solve()
{
    if(n & 1) return 1;
    for(int i=0; i<101; ++i) if(cnt[i] & 1) return 1;
    return 0;
}

int main()
{
    while(scanf("%d", &n) && n)
    {
        int x;
        memset(cnt, 0, sizeof cnt);
        for(int i=0; i<n; ++i) scanf("%d", &x), cnt[x]++;
        printf("%d\n", solve());
    }
}
