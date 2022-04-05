#include <iostream>
#include <cmath>
using namespace std;

int a, b, ra, rb;
double res = -1;

int gcd(int a, int b)
{
    if(b==0) return a;
    return gcd(b, a%b);
}

void check(int aa, int bb)
{
    int d = gcd(aa, bb);
    aa /= d; bb /= d;
    if(aa==a&&bb==b) return;
    if(res==-1)
    {
        res = 1;
        ra = aa;
        rb = bb;
        return;
    }
    int t1 = abs(aa*b-bb*a);
    int t2 = abs(ra*b-rb*a);
    if(t1*rb-t2*bb<0)
    {
        ra = aa;
        rb = bb;
    }
}

void binary(int ll)
{
    int l, r, mid;
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
    for(int i=2; i<=32767; ++i)
        binary(i);
    printf("%d %d\n", ra, rb);
}

int main()
{
    scanf("%d%d", &a, &b);
    process();
    return 0;
}

