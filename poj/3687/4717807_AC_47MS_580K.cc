#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

int N, M;
int cnt[201], d[201];
int Q[201], sz;
vector< vector<int> > g(201);
priority_queue<int> pq;

void init()
{
    memset(cnt, 0, sizeof cnt);
    memset(d, 0, sizeof d);
    scanf("%d%d", &N, &M);
    for(int i=0; i<201; ++i) g[i].clear();
    
    for(int i=0; i<M; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        g[b].push_back(a);
        d[a]++;
    }
}

void out()
{
    for(int i=1; i<N; ++i) printf("%d ", Q[i]);
    printf("%d\n", Q[N]);
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
        Q[k] = N+1-i;
        for(int j=0; j<g[k].size(); ++j)
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

