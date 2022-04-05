#include <stdio.h>
#include <cstring>
#include <cmath>
#define MaxN 300
#define INF 0x3f3f3f3f
#define min(a,b) ((a<b)?a:b)

struct Edge
{
    int idx, f;
    Edge *next, *opp;
}
adj[MaxN], memo[MaxN * MaxN];

int n, x[MaxN], y[MaxN], c[MaxN], lit[MaxN], s, t, sum, sz, mset;
double d;
int P[MaxN], top;
int lv[MaxN], head, tail, Q[MaxN], ST[MaxN];
Edge *pre[MaxN], *cur[MaxN];

void addEdgeProcess(int a, int b, int c){
	Edge* ptr=&memo[mset++];
	ptr->idx=b; ptr->f=c;
	ptr->next=adj[a].next;
	adj[a].next=ptr;
}

void addEdge(int a, int b, int c){
	addEdgeProcess(a, b, c);
	addEdgeProcess(b, a, 0);
	adj[a].next->opp=&memo[mset-1];
	adj[b].next->opp=&memo[mset-2];
}

double dist(int a, int b)
{
    return sqrt((x[a]-x[b]) * (x[a]-x[b]) + (y[a]-y[b]) * (y[a]-y[b]));
}

void make_Gra()
{
    mset = 0;
    s = 0, t = 2 * n + 1;
    for(int i=s; i<=t; ++i) adj[i].next = NULL;

    for(int i=1; i<=n; ++i)
    {
        addEdge(i, i+n, lit[i]);
        if(c[i] > 0) addEdge(s, i, c[i]);
        for(int j=i+1; j<=n; ++j)
        {
            if(dist(i, j) <= d)
            {
                addEdge(i+n, j, INF);
                addEdge(j+n, i, INF);
            }
        }
    }
}

void init()
{
    scanf("%d%lf", &n, &d);
    sum = 0;
    for(int i=1; i<=n; ++i)
    {
        scanf("%d%d%d%d", &x[i], &y[i], &c[i], &lit[i]);
        sum += c[i];
    }
}

bool bfs(int s, int t)
{
    memset(lv, -1, sizeof lv);
    lv[s] = 0; tail = 1; Q[head = 0] = s;
    
    while(head < tail)
    {
        int k = Q[head];
        for(Edge *ptr=adj[k].next; ptr; ptr=ptr->next)
        {
            if(ptr->f>0 && lv[ptr->idx]==-1)
            {
                Q[tail++] = ptr->idx;
                lv[ptr->idx] = lv[k] + 1;
            }
        }
        head++;
    }
    return lv[t] != -1;
}

int Dinic(int s, int t)
{
    int u, v, flow = 0;
    while(bfs(s, t))
    {
        for(int i=s; i<=2*n+1; ++i) cur[i] = adj[i].next;
        P[top = 1] = u = s;
        while(cur[s])
        {
            if(u!=t && cur[u] && cur[u]->f>0 && lv[cur[u]->idx]==lv[u]+1)
            {
                v = cur[u]->idx;
                P[++top] = v;
                pre[v] = cur[u];
                u = v;
            }
            else if(u==t)
            {
                int Min = INF;
                for(int i=top; i>1; --i) Min = min(Min, (pre[P[i]]->f));
                for(int i=top; i>1; --i)
                {
                    pre[P[i]]->f -= Min;
                    pre[P[i]]->opp->f += Min;
                    if(pre[P[i]]->f==0) top = i - 1;
                }
                u = P[top];
                flow += Min;
            }
            else
            {
                while(u != s && cur[u]==NULL) u = P[--top];
                cur[u] = cur[u]->next;
            }
        }
    }
    return flow;
}

void solve()
{
    sz = 0;
    for(int i=1; i<=n; ++i)
    {
        make_Gra();
        int k = Dinic(s, i);
        if(k == sum) ST[++sz] = i-1;
    }
    if(sz==0) printf("-1\n");
    else
    {
        for(int i=1; i<sz; ++i) printf("%d ", ST[i]);
        printf("%d\n", ST[sz]);
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        init();
        solve();
    }
    return 0;
}

