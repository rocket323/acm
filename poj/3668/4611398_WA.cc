#include <iostream>
#include <cmath>
#include <algorithm>
#define eps 9e-7
#define INF 1e20
using namespace std;

int x[201], y[201], N;
double E[20010];

void init()
{
    scanf("%d", &N);
    for(int i=1; i<=N; ++i)
        scanf("%d%d", &x[i], &y[i]);
}

void solve()
{
    int sz = 0, cnt = 0;
    for(int i=1; i<N; ++i)
        for(int j=i+1; j<=N; ++j)
        {
            if(fabs(x[i]-x[j])<eps)
                E[sz] = INF;
            else E[sz] = (y[i]-y[j])/(x[i]-x[j]+0.0);
            sz++;
        }

    sort(E, E+sz);

    int i = 0;
    while(i<sz)
    {
        cnt++;
        double t = E[i];
        ++i;
        while(i<sz&&fabs(E[i]-t)<eps) ++i;
    }
    printf("%d\n", cnt);
}

int main()
{
    init();
    solve();
    return 0;
}

