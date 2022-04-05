#include <iostream>
#include <cmath>
using namespace std;

long long a, b, ra, rb;
long long res = -1;

long long gcd(long long a, long long b)
{
    if(b==0) return a;
    return gcd(b, a%b);
}

void check(long long aa, long long bb)
{
    long long d = gcd(aa, bb);
    aa /= d; bb /= d;
    if(aa==a&&bb==b) return;
    if(res==-1)
    {
        res = 1;
        ra = aa;
        rb = bb;
        return;
    }
    long long t1 = abs(aa*b-bb*a);
    long long t2 = abs(ra*b-rb*a);
    if(t1*rb-t2*bb<0)
    {
        ra = aa;
        rb = bb;
    }
    if(t1*rb-t2*bb==0&&aa*rb-bb*ra<0)
    {
        ra = aa;
        rb = bb;
    }
}

void binary(long long ll)
{
    long long l, r, mid;
    l=1; r=ll-1;
    while(l<=r)
    {
        mid = (l+r)>>1;
        double tmp = mid/(ll+0.0);
        check(mid, ll);
        if(mid*b-a*ll<0)
            l = mid+1;
        else r = mid-1;
    }
}

void process()
{
    for(long long i=2; i<=32767; ++i)
        binary(i);
    printf("%I64d %I64d\n", ra, rb);
}

int main()
{
    scanf("%I64d%I64d", &a, &b);
    process();
    return 0;
}

