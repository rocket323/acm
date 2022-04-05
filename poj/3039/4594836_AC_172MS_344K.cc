#include <iostream>
#include <cmath>
#define eps 1e-8
using namespace std;

int a = 10, b = 1;
double res;
double sss;
int N, D;

int gcd(int a, int b)
{
    if(b==0) return a;
    return gcd(b, a%b);
}

void go(int u, int d)
{
    int p = gcd(u, d);
    u /= p; d /= p;
    double tmp = u/(d+0.0);
    double t1 = fabs(tmp-sss);
    double t2 = fabs(res-sss);
    if(t1<t2)
    {
        res = tmp;
        a = u;
        b = d;
    }
}

void check(int l)
{
    int u = l*N/D;
    if(u*D==l*N)
    {
        go(u-1, l);
        go(u+1, l);
    }
    else
    {
        go(u, l);
        go(u+1, l);
    }
}

void solve()
{
    res = 100000000;
    sss = N/(D+0.0);
    for(int i=2; i<=32767; ++i)
        check(i);
    printf("%d %d\n", a, b);
}

int main()
{
    while(scanf("%d%d", &N, &D)!=EOF)
        solve();
    return 0;
}

