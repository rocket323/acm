#include <iostream>
#include <algorithm>
#include <cmath>
#define MaxN 500010
#define INF 1000000001
#define ll long long
using namespace std;

int x[MaxN], N;

void init()
{
    for(int i=0; i<N; ++i)
        scanf("%d", &x[i]);
    sort(x, x+N);
}

int getSum(int idx, int num)
{
    int l=0, r=idx-1, mid, res = idx;
    while(l<=r)
    {
        mid = (l+r)>>1;
        if(x[idx]-x[mid]<=num)
        {
            res = mid;
            r = mid-1;
        }
        else l = mid+1;
    }
    return idx-res;
}

int cnt(int num)
{
    int sum = 0;
    for(int i=1; i<N; ++i)
    {
        sum += getSum(i, num);
    }
    return sum;
}

void solve()
{
    int l=0, r=x[N-1]-x[0], mid, res = -1;
    long long key = ((ll)(N-1)*(ll)N/2+1)/2;

    while(l<=r)
    {
        mid = ((ll)l+(ll)r)>>1;
        long long k = cnt(mid);
        if(k>=key)
        {
            res = mid;
            r = mid-1;
        }
        else l = mid+1;
    }
    printf("%d\n", res);
}

int main()
{
    while(scanf("%d", &N)!=EOF)
    {
        init();
        solve();
    }
    return 0;
}

