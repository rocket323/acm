#include <iostream>
#include <cmath>
#define lo long long
using namespace std;

long long a, b, ra, rb;
long long res = -1;

long long gcd(long long aa, long long bb)
{
    if(bb==0) return aa;
    return gcd(bb, aa%bb);
}

void check(long long aa, long long bb)
{
    if(aa==a&&bb==b) return;
    if(res==-1)
    {
        res = 1;
        ra = aa;
        rb = bb;
        return;
    }
    long long t1 = abs((lo)aa*(lo)b-(lo)bb*(lo)a);
    long long t2 = abs((lo)ra*(lo)b-(lo)rb*(lo)a);
    if((lo)t1*(lo)rb-(lo)t2*(lo)bb<0)
    {
        ra = aa;
        rb = bb;
        return;
    }
    if((lo)t1*(lo)rb-(lo)t2*(lo)bb==0&&(lo)aa*(lo)rb-(lo)bb*(lo)ra<0)
    {
        ra = aa;
        rb = bb;
        return;
    }
}

void binary(long long ll)
{
    long long l, r, mid;
    l=1; r=ll-1;
    if(ll==2)
    {
		check(1, 2);
		return;
	}
    while(l<=r)
    {
        mid = ((lo)l+(lo)r) / 2;
        long long d = gcd(mid, ll);
        if(d==1)
			check(mid, ll);
        if((lo)mid*(lo)b-(lo)a*(lo)ll<0)
            l = mid+1;
        else r = mid-1;
    }
}

void process()
{
    res = -1;
    for(long long i=2; i<=32767; ++i)
        binary(i);
    printf("%I64d %I64d\n", ra, rb);
}

int main()
{
	//freopen("data.in", "r", stdin);
    while(scanf("%I64d%I64d", &a, &b)!=EOF)
    	process();
    //while(1);
    return 0;
}

