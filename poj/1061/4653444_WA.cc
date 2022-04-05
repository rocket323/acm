#include <iostream>
#include <cmath>
using namespace std;

int x, y, m, n, L, s, ss, T1, T2, d, L1, L2, T;

int mod(int x, int n)
{
    return (x%n+n)%n;
}

void gcd(int a, int b, int& d, int& x, int& y)
{
    if(b==0){ d=a; x=1; y=0; }
    else
    {
        gcd(b, a%b, d, y, x);
        y -= (a/b)*x;
    }
}

int solve()
{

    m = m-n; y = y-x;
    gcd(m, L, d, T, s);

    if(y%d!=0) return -1;

    T *= (y/d);

    return mod(T, abs(L/d));
}

int main()
{
    
    while(scanf("%d%d%d%d%d", &x, &y, &m, &n, &L)!=EOF)
    {
        x%=L, y%=L, m%=L, n%=L;
        int k = solve();
        if(k==-1) printf("Impossible\n");
        else printf("%d\n", k);
    }
    return 0;
}

