#include <stdio.h>
#include <algorithm>
#define MaxN 1000020

int N, S, L[20000];
int C[MaxN+10];

int lowbit(int x){ return x&(-x); }

void add(int now)
{
    while(now<MaxN)
    {
        C[now]++;
        now += lowbit(now);
    }
}

int getSum(int now)
{
    int ans = 0;
    while(now)
    {
        ans += C[now];
        now -= lowbit(now);
    }
    return ans;
}

void process()
{
    int cnt = 0;
    memset(C, 0, sizeof C);
    for(int i=0; i<N; ++i)
    {
        scanf("%d", &L[i]);
        add(L[i]);
    }
    for(int i=0; i<N; ++i)
        if(S>L[i])
        {
            cnt += getSum(S-L[i]);
            if(L[i]+L[i]<=S) cnt--;
        }
    printf("%d\n", cnt/2);
}

int main()
{
    scanf("%d%d", &N, &S);
    process();
    return 0;
}
