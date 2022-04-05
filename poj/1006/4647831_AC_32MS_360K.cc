#include <iostream>
#define L 21252
using namespace std;

int p, e, i, d;
int T[4], m[4], x[4], y[4], dd;

void gcd(int a, int b, int& dd, int& x, int& y)
{
    if(b==0){ dd=a; x=1; y=0; }
    else
    {
        gcd(b, a%b, dd, y, x);
        y -= (a/b)*x;
    }
}

int mod(int x, int n)
{
    return (x%n+n)%n;
}

void solve(int cas)
{
    int res = 0;
    T[1] = 23; T[2] = 28; T[3] = 33;
    for(int i=1; i<=3; ++i)
    {
        gcd(L/T[i], T[i], dd, x[i], y[i]);
        res += L/T[i]*x[i]*m[i];
    }
    res = mod(res, L);
    if(res<=d) res += L;
    printf("Case %d: the next triple peak occurs in %d days.\n", cas, res-d);
}

int main()
{
    int k=0;
    while(scanf("%d%d%d%d", &m[1], &m[2], &m[3], &d), m[1]!=-1)
    {
        solve(++k);
    }
    return 0;
}

