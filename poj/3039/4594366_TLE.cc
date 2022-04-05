#include <iostream>
#include <cmath>
#define lo long long
using namespace std;

long long a, b, ra, rb;
long long res = -1;

long long gcd(long long a, long long b)
{
    if(b==0) return a;
    return gcd(b, a%b);
}

void check(long long aaa, long long bbb)
{
    long long d = gcd(aaa, bbb);
    long long aa = aaa/d; 
    long long bb = bbb/d;
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
    while(l<=r)
    {
        mid = ((lo)l+(lo)r) / 2;
        check(mid, ll);
        if((lo)mid*(lo)b-(lo)a*(lo)ll<0)
            l = mid+1;
        else r = mid-1;
    }
}

void process()
{
    res = -1;
    for(int i=2; i<=32767; ++i)
        binary(i);
    cout<<ra<<' '<<rb<<endl;
}

int main()
{
    cin>>a>>b;
        process();
    return 0;
}

