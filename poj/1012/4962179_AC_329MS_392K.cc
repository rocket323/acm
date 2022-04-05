#include <iostream>
using namespace std;

int a[15];

int solve(int n)
{
    int ans = 2;
    int cnt;
    while(true)
    {
        int flag = 1;
        int p = (ans-1) % (2*n);
        if(p < n) flag = 0;
        cnt = 1;
        for(int i=1; i<n && flag; ++i)
        {
            p = (p -1 + ans) % (2*n - cnt);
            if(p < n) flag = 0;
            cnt++;
        }
        if(flag) return ans;
        ans++;
    }
}

int main()
{
    for(int i=1; i<14; ++i)
    {
        a[i] = solve(i);
    }
    int n;
    while(scanf("%d", &n) && n) printf("%d\n", a[n]);
    return 0;
}

