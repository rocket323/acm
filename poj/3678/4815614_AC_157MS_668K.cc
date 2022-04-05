#include <iostream>
#define MaxL 2000
#define UNVIS 0
#define VIS 1
#define OVER 2
using namespace std;

struct Edge
{
    int idx;
    Edge * next;
}
adj[MaxL], memo[4000010];

int N, M, lt, sz, mset;
int S[MaxL], id[MaxL], low[MaxL], pre[MaxL], mark[MaxL];

void addEdge(int a, int b)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void init()
{
    scanf("%d%d", &N, &M);

    mset = 0;
    for(int i=0; i<2*N; ++i) adj[i].next = NULL;

    for(int i=0; i<M; ++i)
    {
        int a, b, c;
        char ch[4];
        scanf("%d%d%d%s", &a, &b, &c, ch);
        
        if(ch[0]=='A')
        {
            if(c==0){ addEdge(a+N, b); addEdge(b+N, a); }
            if(c==1){ addEdge(a+N, b+N); addEdge(b+N, a+N); addEdge(a, a+N); addEdge(b, b+N); }
        }
        
        if(ch[0]=='O')
        {
            if(c==0){ addEdge(a, b); addEdge(b, a); addEdge(a+N, a); addEdge(b+N, b); }
            if(c==1){ addEdge(a, b+N); addEdge(b, a+N); }
        }

        if(ch[0]=='X')
        {
            if(c==0){ addEdge(a, b); addEdge(b, a); addEdge(a+N, b+N); addEdge(b+N, a+N); }
            if(c==1){ addEdge(a, b+N); addEdge(b+N, a); addEdge(a+N, b); addEdge(b, a+N); }
        }
    }
}

void dfs(int now)
{
    mark[now] = VIS;
    id[now] = low[now] = lt++;
    S[++sz] = now;

    Edge * ptr = adj[now].next;
    while(ptr)
    {
        int k = ptr->idx;
        if(mark[k]==UNVIS)
        {
            dfs(k);
            if(low[k]<low[now]) low[now] = low[k];
        }
        else if(mark[k]==VIS)
        {
            if(low[k]<low[now]) low[now] = low[k];
        }
        ptr = ptr->next;
    }
    if(id[now]==low[now])
    {
        do
        {
            pre[S[sz]] = now;
            mark[S[sz]] = OVER;
        }
        while(S[sz--]!=now);
    }
}

void solve()
{

    lt = sz = 0;

    memset(mark, 0, sizeof mark);
    for(int i=0; i<2*N; ++i)
        if(mark[i]==UNVIS) dfs(i);

    for(int i=0; i<N; ++i)
        if(pre[i]==pre[i+N])
        {
            printf("NO\n");
            return;
        }
    printf("YES\n");
}

int main()
{
    init();
    solve();
    return 0;
}

