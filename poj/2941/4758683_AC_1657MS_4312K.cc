#include <iostream>
using namespace std;

int a[1001][1001], N;

void init()
{
    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j)
            scanf("%d", &a[i][j]);
}

void solve()
{
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
            if(a[i][i]+a[j][j]!=a[i][j]+a[j][i])
            {
                printf("not homogeneous\n");
                return;
            }
    }
    printf("homogeneous\n");
}

int main()
{
    while(scanf("%d", &N) && N)
    {
        init();
        solve();
    }
    return 0;
}

