#include <iostream>
#include <stdio.h>
#include <cstring>
#define MaxN 1000010
#define INF 2000000000
using namespace std;

int N, K;
int w[MaxN], Q[MaxN];
int head, tail;
int res[2][MaxN];

void init()
{
    for(int i=1; i<=N; ++i)
        scanf("%d", &w[i]);
}

int cmp1(int a, int b){ return a>=b; }
int cmp2(int a, int b){ return a<=b; }


void go1(int A[], int cal)
{
    Q[head = 1] = 1;
    tail = 2;
    A[1] = w[1];

    for(int i=2; i<=N; ++i)
    {
        while(head<tail && Q[head]<i-K+1) ++head;
        A[i] = w[Q[head]];
        if(K==1) A[i] = cal;
        if(cmp1(w[i], A[i])) A[i] = w[i];

        while(head<tail && cmp1(w[i], w[Q[tail-1]])) --tail;
        Q[tail] = i;
        ++tail;
    }
}

void go2(int A[], int cal)
{
    Q[head = 1] = 1;
    tail = 2;
    A[1] = w[1];

    for(int i=2; i<=N; ++i)
    {
        while(head<tail && Q[head]<i-K+1) ++head;
        A[i] = w[Q[head]];
        if(K==1) A[i] = cal;
        if(cmp2(w[i], A[i])) A[i] = w[i];

        while(head<tail && cmp2(w[i], w[Q[tail-1]])) --tail;
        Q[tail] = i;
        ++tail;
    }
}

void out()
{
    for(int i=K; i<N; ++i)
        printf("%d ", res[0][i]);
    printf("%d\n", res[0][N]);

    for(int i=K; i<N; ++i)
        printf("%d ", res[1][i]);
    printf("%d\n", res[1][N]);
}

void solve()
{
    go2(res[0], INF);
    go1(res[1], -INF);

    out();
}

int main()
{
    while(scanf("%d%d", &N, &K)!=EOF)
    {
        init();
        solve();
    }
    return 0;
}

