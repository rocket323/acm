#include <iostream>
#define MaxN 10010
using namespace std;

struct Edge{
    int idx;
    Edge * next;
}adj[MaxN];

int N, p[MaxN], size[MaxN], par[MaxN];
Edge memo[2*MaxN];
int mset;

void addEdge(int a, int b)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void dfs(int now)
{
    Edge* ptr = adj[now].next;
    size[now] = 1;
    while(ptr)
    {
        int k = ptr->idx;
        if(p[now]!=k)
        {
            p[k] = now;
            dfs(k);
            size[now] += size[k];
        }
        ptr = ptr->next;
    }
}

void init()
{
    scanf("%d", &N);
    for(int i=1; i<=N; ++i) adj[i].next = NULL;
    mset = 0;
    for(int i=1; i<N; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    memset(p, -1, sizeof p);
    memset(size, 0, sizeof size);
    dfs(1);
}

void process()
{
    bool flag = 0;
    memset(par, -1, sizeof par);
    for(int i=1; i<=N; ++i)
    {
        Edge* ptr = adj[i].next;
        while(ptr)
        {
            if(size[ptr->idx]>par[i]&&p[ptr->idx]==i)
                par[i] = size[ptr->idx];
            ptr = ptr->next;
        }
        if(N-size[i]>par[i])
            par[i] = N-size[i];
        if(par[i]<=N/2)
        {
            flag = 1;
            printf("%d\n", i);
        }
    }
    if(!flag) printf("NONE\n");
}

int main()
{
    init();
    process();
    return 0;
}

