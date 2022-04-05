#include <iostream>
#include <cmath>
using namespace std;

long long x, y, m, n, L, s, ss, T1, T2, d, L1, L2, T;

long long mod(long long x, long long n)
{
    return (x%n+n)%n;
}

void gcd(long long a, long long b, long long& d, long long& x, long long& y)
{
    if(b==0){ d=a; x=1; y=0; }
    else
    {
        gcd(b, a%b, d, y, x);
        y -= (a/b)*x;
    }
}

long long solve()
{

    m = m-n; y = y-x;
    gcd(m, L, d, T, s);

    if(y%d!=0) return -1;

    T *= (y/d);

    return mod(T, abs(L/d));
}

int main()
{
    
    while(scanf("%I64d%I64d%I64d%I64d%I64d", &x, &y, &m, &n, &L)!=EOF)
    {
        x%=L, y%=L, m%=L, n%=L;
        long long k = solve();
        if(k==-1) printf("Impossible\n");
        else printf("%I64d\n", k);
    }
    return 0;
}

