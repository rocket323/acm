#include <iostream>
#include <sstream>
#define MaxL 2000
#define INF 10000000
using namespace std;

struct Edge
{
    int idx, f, save;
    Edge * next, * opp;
}
adj[MaxL], memo[MaxL*MaxL*10];
Edge * pre[MaxL], *cur[MaxL];

int N, M, mset;
int lv[MaxL], Q[MaxL], head, tail, Path[MaxL], top;
int g[MaxL][MaxL];

void addEdgeProcess(int a, int b, int c)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->f = ptr->save = c;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void add(int a, int b, int c)
{
    addEdgeProcess(a, b, c);
    addEdgeProcess(b, a, 0);
    adj[a].next->opp = &memo[mset-1];
    adj[b].next->opp = &memo[mset-2];
}

void addEdge(int a, int b, int c)
{
    add(a, b, c);
    //add(b, a, c);
}

void init()
{

    mset = 0;
    for(int i=0; i<MaxL; ++i) adj[i].next = NULL;
    memset(g, 0, sizeof g);

    char S[1000], ch;
    for(int i=0; i<N; ++i) addEdge(i, i+N, 1);
    for(int i=0; i<M; ++i)
    {
        cin>>S;
        istringstream in(S);
        int a, b;
        in>>ch>>a>>ch>>b>>ch;
        addEdge(a+N, b, INF);
        addEdge(b+N, a, INF);
        g[a][b] =g[b][a] = 1;
    }
}

bool bfs(int S, int T)
{
    memset(lv, -1, sizeof lv);
    Q[head=tail] = S;
    lv[S] = 1;
    while(head<=tail)
    {
        int k = Q[head];
        Edge * ptr = adj[k].next;
        while(ptr)
        {
            if(lv[ptr->idx]==-1&&ptr->f>0)
            {
                lv[ptr->idx] = lv[k] + 1;
                Q[++tail] = ptr->idx;
            }
            ptr = ptr->next;
        }
        ++head;
    }
    return lv[T]!=-1;
}

int Min(int a, int b){ return (a<b)?a:b; }

int max_flow(int S, int T)
{
    int u, flow = 0;
    while(bfs(S, T))
    {
        Path[top = 1] = u = S;
        for(int i=0; i<2*N; ++i) cur[i] = adj[i].next;
        while(cur[S])
        {
            if(u!=T&&cur[u]&&cur[u]->f>0&&lv[cur[u]->idx]==lv[u]+1)
            {
                int v = cur[u]->idx;
                pre[v] = cur[u];
                Path[++top] = v;
                u = v;
            }
            else if(u==T)
            {
                int tmp = INF;
                for(int i=top; i>1; --i) tmp = Min(tmp, pre[Path[i]]->f);
                for(int i=top; i>1; --i)
                {
                    pre[Path[i]]->f -= tmp;
                    pre[Path[i]]->opp->f += tmp;
                    if(pre[Path[i]]->f==0) top = i-1;
                }
                u = Path[top];
                flow += tmp;
            }
            else
            {
                while(u!=S&&cur[u]==NULL) u = Path[--top];
                cur[u] = cur[u]->next;
            }
        }
    }
    return flow;
}

void restore()
{
    for(int i=0; i<2*N; ++i)
    {
        Edge * ptr = adj[i].next;
        while(ptr)
        {
            ptr->f = ptr->save;
            ptr = ptr->next;
        }
    }
}

void solve()
{
    int ans = INF + 100;
    /*for(int i=0; i<2*N; ++i)
    {
        Edge * ptr = adj[i].next;
        while(ptr)
        {
            cout<<i<<' '<<ptr->idx<<' '<<ptr->f<<endl;
            ptr = ptr->next;
        }
    }*/
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            if(i==j||g[i][j]) continue;
            restore();
            int k = max_flow(i+N, j);
            if(k>=INF) k = N;
            if(k<ans) ans = k;
        }
    }
    if(ans>=INF) ans = N;
    printf("%d\n", ans);
}

int main()
{
    while((cin>>N>>M))
    {
        init();
        //solve();
    }
    return 0;
}

