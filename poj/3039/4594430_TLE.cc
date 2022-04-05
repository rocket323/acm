#include <iostream>
#include <cmath>
#define lo long long
using namespace std;

int a, b, ra, rb;
int res = -1;

int gcd(int aa, int bb)
{
    if(bb==0) return aa;
    return gcd(bb, aa%bb);
}

void check(int aaa, int bbb)
{
    int d = gcd(aaa, bbb);
    int aa = aaa/d; 
    int bb = bbb/d;
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

void binary(int ll)
{
    int l, r, mid;
    l=1; r=ll-1;
    if(ll==2)
    {
		check(1, 2);
		return;
	}
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
	//freopen("data.in", "r", stdin);
    while(cin>>a>>b)
    	process();
    //while(1);
    return 0;
}

