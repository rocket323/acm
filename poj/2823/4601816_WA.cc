#include <iostream>
#define MaxN 1000010
#define INF 2000000000
using namespace std;

long long N, K;
long long w[MaxN], Q[MaxN];
long long head, tail;
long long res[2][MaxN];

void init()
{
    for(long long i=1; i<=N; ++i)
        scanf("%I64d", &w[i]);
}

long long cmp1(long long a, long long b){ return a>=b; }
long long cmp2(long long a, long long b){ return a<=b; }

void outQ()
{
    for(long long i=head; i<tail; ++i)
        cout<<Q[i]<<' ';
    cout<<endl;
}

void go(long long cmp(long long, long long), long long A[])
{
    Q[head = 1] = 1;
    tail = 2;
    A[1] = w[1];


    for(long long i=2; i<=N; ++i)
    {
        while(head<tail && Q[head]<i-K+1) ++head;
        A[i] = w[Q[head]];
        if(cmp(w[i], A[i])) A[i] = w[i];

        while(head<tail && cmp(w[i], w[Q[tail-1]])) --tail;
        Q[tail] = i;
        ++tail;
    }
}

void out()
{
    for(long long i=K; i<N; ++i)
        printf("%I64d ", res[0][i]);
    printf("%I64d\n", res[0][N]);

    for(long long i=K; i<N; ++i)
        printf("%I64d ", res[1][i]);
    printf("%I64d\n", res[1][N]);
}

void solve()
{
    long long (*pfun)(long long, long long);
    pfun = &cmp2;
    go(pfun, res[0]);
    pfun = &cmp1;
    go(pfun, res[1]);

    out();
}

int main()
{
    //freopen("2823.in", "r", stdin);
    //freopen("ooo.out", "w", stdout);
    while(scanf("%I64d%I64d", &N, &K)!=EOF)
    {
        init();
        solve();
    }
    return 0;
}

