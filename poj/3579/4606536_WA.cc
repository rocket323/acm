#include <iostream>
#include <algorithm>
#include <cmath>
#define MaxN 100010
#define INF 1000000001
#define ll long long
using namespace std;

long long x[MaxN], N;

void init()
{
    for(long long i=0; i<N; ++i)
        scanf("%I64d", &x[i]);
    sort(x, x+N);
}

long long getSum(long long idx, long long num)
{
    long long l=0, r=idx-1, mid, res = idx;
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

long long cnt(long long num)
{
    long long sum = 0;
    for(long long i=1; i<N; ++i)
    {
        sum += getSum(i, num);
    }
    return sum;
}

void solve()
{
    long long l=x[1]-x[0], r=x[N-1]-x[0], mid, res = -1;
    long long key = ((ll)(N-1)*(ll)N/2)/2;

    while(l<=r)
    {
        mid = (l+r)>>1;
        long long k = cnt(mid);
        if(k>=key)
        {
            res = mid;
            r = mid-1;
        }
        else l = mid+1;
    }
    printf("%I64d\n", res);
}

int main()
{
    while(scanf("%I64d", &N)!=EOF)
    {
        init();
        solve();
    }
    return 0;
}

