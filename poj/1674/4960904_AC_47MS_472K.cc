#include <iostream>
using namespace std;

int a[10010], n;
int mark[10010];

void solve()
{
    scanf("%d", &n);
    for(int i=1; i<=n; ++i) scanf("%d", &a[i]);

    int ans = 0;
    memset(mark, -1, sizeof mark);
    for(int i=1; i<=n; ++i)
    {
        if(mark[i]==1) continue;
        int cnt = 1;
        mark[i] = 1;
        int j = a[i];
        while(mark[j]==-1)
        {
            mark[j] = 1;
            cnt++;
            j = a[j];
        }
        ans += cnt-1;
    }
    printf("%d\n", ans);
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        solve();
    }
    return 0;
}

