#include <iostream>
#include <cmath>
#define eps 1e-7
using namespace std;

struct Edge
{
    int a, b;
    bool vis;
}E[20010];

int x[201], y[201], N;

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
            E[sz].a = i;
            E[sz].b = j;
            E[sz].vis = 0;
            sz++;
        }
    for(int i=0; i<sz; ++i)
    {
        if(E[i].vis) continue;
        E[i].vis = 1;
        cnt++;
        for(int j=i+1; j<sz; ++j)
        {
            double t1 = (y[E[i].a]-y[E[i].b])/(x[E[i].a]-x[E[i].b]+0.0);
            double t2 = (y[E[j].a]-y[E[j].b])/(x[E[j].a]-x[E[j].b]+0.0);
            if(fabs(t1-t2)<eps)
            {
                E[j].vis = 1;
            }
        }
    }
    printf("%d\n", cnt);
}

int main()
{
    init();
    solve();
    return 0;
}
