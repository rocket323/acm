#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

int N, M;
int cnt[201], d[201];
int g[201][201], Q[201], sz;
priority_queue<int> pq;

void init()
{
    memset(cnt, 0, sizeof cnt);
    memset(d, 0, sizeof d);
    scanf("%d%d", &N, &M);
    for(int i=0; i<M; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        g[b][++cnt[b]] = a;
        d[a]++;
    }
}

void out()
{
    for(int i=sz-1; i>0; --i) printf("%d ", Q[i]);
    printf("%d\n", Q[0]);
}

int solve()
{
    for(int i=1; i<=N; ++i)
    {
        if(d[i]==0) pq.push(i);
    }
    sz = 0;
    for(int i=1; i<=N; ++i)
    {
        if(pq.empty()) return -1;
        int k = pq.top();
        pq.pop();
        Q[sz++] = k;
        for(int j=1; j<=cnt[k]; ++j)
        {
            d[g[k][j]]--;
            if(d[g[k][j]]==0) pq.push(g[k][j]);
        }
    }
    return 0;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        init();
        if(solve()==-1) printf("-1\n");
        else out();
    }
    return 0;
}

