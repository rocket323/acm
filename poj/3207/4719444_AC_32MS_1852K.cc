#include <iostream>
#include <cmath>
#define MaxM 1010
#define UNVIS 0
#define VIS 1
#define OVER 2
using namespace std;

struct Edge
{
    int idx;
    Edge * next;
};
Edge adj[MaxM], memo[500*MaxM];

int Ea[MaxM], Eb[MaxM], vis[MaxM];
int N, M, mset;
int id[MaxM], low[MaxM], pre[MaxM];
int S[MaxM], sz, lv;

int opp(int x)
{
    return (x<M)?(x+M):(x-M);
}

bool cross(int i, int j)
{
    if(Ea[i]<Ea[j]&&Ea[j]<Eb[i]&&Eb[j]>Eb[i]) return 1;
    if(Ea[i]<Eb[j]&&Eb[j]<Eb[i]&&Ea[j]<Ea[i]) return 1;
    return 0;
}

void addEdge(int a, int idx)
{
    Edge* ptr = &memo[mset++];
    ptr->idx = idx;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void init()
{
    mset = 0;
    for(int i=0; i<M; ++i)
    {
        scanf("%d%d", &Ea[i], &Eb[i]);
        if(Ea[i]>Eb[i])
        {
            int t = Ea[i];
            Ea[i] = Eb[i];
            Eb[i] = t;
        }
    }
    for(int i=0; i<2*M; ++i) adj[i].next = NULL;

    for(int i=0; i<M; ++i)
    {
        for(int j=i+1; j<M; ++j)
        {
            if(cross(i, j))
            {
                addEdge(i, opp(j));
                addEdge(j, opp(i));
                addEdge(opp(i), j);
                addEdge(opp(j), i);
            }
        }
    }
}

void dfs(int now)
{
    id[now] = low[now] = lv++;
    S[++sz] = now;
    vis[now] = VIS;
    
    Edge* ptr = adj[now].next;
    while(ptr)
    {
        int k = ptr->idx;
        if(vis[k]==UNVIS)
        {
            dfs(k);
            if(low[k]<low[now]) low[now] = low[k];
        }
        else if(vis[k]==VIS)
        {
            if(low[k]<low[now]) low[now] = low[k];
        }
        ptr = ptr->next;
    }

    if(low[now] == id[now])
    {
        do
        {
            pre[S[sz]] = now;
            vis[S[sz]] = OVER;
        }while(S[sz--]!=now);
    }
}

void solve()
{
    memset(vis, 0, sizeof vis);
    lv = sz = 0;
    for(int i=0; i<2*M; ++i) pre[i] = i;

    for(int i=0; i<2*M; ++i)
    {
        if(vis[i]==0)
        {
            dfs(i);
        }
    }

    for(int i=0; i<2*M; ++i)
        if(pre[i]==pre[opp(i)])
        {
            printf("the evil panda is lying again\n");
            return;
        }
    printf("panda is telling the truth...\n");
}

int main()
{
    while(scanf("%d%d", &N, &M)!=EOF)
    {
        init();
        solve();
    }
    return 0;
}

