#include <iostream>
#define MaxN 1000001
using namespace std;

int f[1000010];
int N;

void init()
{
    memset(f, -1, sizeof f);
    for(int i=2; i<MaxN; ++i)
    {
        if(f[i]!=-1) continue;
        int j = i+i;
        while(j<MaxN)
        {
            f[j] = 0;
            j += i;
        }
    }
    f[2] = 0;
}

void solve()
{
    for(int i=3; i<=(N+1)/2; ++i)
        if(f[i]==-1&&f[N-i]==-1)
        {
            printf("%d = %d + %d\n", N, i, N-i);
            return;
        }
    printf("Goldbach's conjecture is wrong.\n");
}

int main()
{
    init();
    while(scanf("%d", &N), N!=0)
    {
        solve();
    }
    return 0;
}

