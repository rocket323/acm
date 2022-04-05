#include <iostream>
#include <sstream>
#include <algorithm>
#define UNVIS 0
#define VIS 1
#define OVER 2
#define MaxL 2010
using namespace std;

struct node
{
    int s, t;
    int c;
}T[MaxL];

struct Edge
{
    int idx;
    Edge * next;
}
adj[MaxL], adj2[MaxL], memo[MaxL*MaxL];

int N, mset;
int Q[MaxL], top;
int id[MaxL], low[MaxL], S[MaxL], sz, pre[MaxL], mark[MaxL];
int lt, col[MaxL], in[MaxL];

int opp(int x){ return (x<N)? x+N : x-N; }

int getTime()
{
    char S[20];
    scanf("%s", S);
    istringstream in(S);

    int a, b;
    char ch;
    in>>a>>ch>>b;
    return a*60+b;
}

void init()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i)
    {
        T[i].s = getTime();
        T[i].t = getTime();
        scanf("%d\n", &T[i].c);
    }
}

bool cross(int a1, int b1, int a2, int b2)
{
    if(a2>=a1&&a2<=b1) return 1;
    if(b2>=a1&&b2<=b1) return 1;
    if(a1>=a2&&a1<=b2) return 1;
    if(b1>=a2&&b1<=b2) return 1;
    return 0;
}

//反向建图
void addEdge(int a, int b)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = a;
    ptr->next = adj[b].next;
    adj[b].next = ptr;
}

void buildGraph()
{
    mset = 0;
    for(int i=0; i<2*N; ++i) adj[i].next = NULL;

    for(int i=0; i<N; ++i)
        for(int j=i+1; j<N; ++j)
        {
            if(cross(T[i].s, T[i].s+T[i].c, T[j].s, T[j].s+T[i].c))
            {
                addEdge(i, j+N);
                addEdge(j, i+N);
            }
            if(cross(T[i].t-T[i].c, T[i].t, T[j].t-T[j].c, T[j].t))
            {
                addEdge(i+N, j);
                addEdge(j+N, i);
            }
            if(cross(T[i].s, T[i].s+T[i].c, T[j].t-T[j].c, T[j].t))
            {
                addEdge(i, j);
                addEdge(j+N, i+N);
            }
            if(cross(T[i].t-T[i].c, T[i].t, T[j].s, T[j].s+T[j].c))
            {
                addEdge(i+N, j+N);
                addEdge(j, i);
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

void addEdge2(int a, int b)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = a;
    ptr->next = adj2[a].next;
    adj2[a].next = ptr;
}

void reBuildGraph()
{
    for(int i=0; i<2*N; ++i) adj2[i].next = NULL;
    memset(in, 0, sizeof in);
    for(int i=0; i<2*N; ++i)
    {
        Edge * ptr = adj[i].next;
        while(ptr)
        {
            int k = ptr->idx;
            if(pre[i]!=pre[k]){ addEdge2(pre[i], pre[k]); in[pre[k]]++; }
            ptr = ptr->next;
        }
    }
}

void visit(int now, int color)
{
    col[now] = color;

    Edge * ptr = adj[now].next;
    while(ptr)
    {
        if(col[ptr->idx]==-1) visit(ptr->idx, color);
        ptr = ptr->next;
    }
}

void topSort()
{
    top = 0;
    for(int i=0; i<2*N; ++i)
    {
        if(pre[i]!=i||in[i]!=0) continue;
        Q[++top] = i;
    }

    memset(col, -1, sizeof col);
    while(top>0)
    {
        int k = Q[top--];
        if(col[k]==-1)
        {
            col[k] = 1;
            visit(pre[opp(k)], 2);
        }
        Edge *ptr = adj[k].next;
        while(ptr)
        {
            in[ptr->idx]--;
            if(in[ptr->idx]==0) Q[++top] = ptr->idx;
            ptr = ptr->next;
        }
    }
}

string process(int num)
{
    string s1="", s2="";
    int h = num / 60;
    int m = num % 60;
    
    stringstream in;

    in<<h; in>>s1;
    if(h==0) s1 = "00";
    else if(h<10) s1 = "0" + s1;

    stringstream in2;
    in2<<m; in2>>s2;
    if(m==0) s2 = "00";
    else if(m<10) s2 = "0" + s2;

    return s1 + ":" + s2;
}

void output()
{
    printf("YES\n");
    for(int i=0; i<N; ++i)
    {
        if(col[i]==1) cout << process(T[i].s) << ' ' << process(T[i].s+T[i].c) << endl;
        else cout << process(T[i].t-T[i].c) << ' ' << process(T[i].t) <<endl ;
    }
}

bool check()
{
    for(int i=0; i<N; ++i)
        if(pre[i]==pre[i+N]) return 0;
    return 1;
}

void solve()
{
    buildGraph();

    lt = sz = 0;
    memset(mark, 0, sizeof mark);
    for(int i=0; i<2*N; ++i)
        if(mark[i]==UNVIS) dfs(i);

    reBuildGraph();

    if(check())
    {
        topSort();
        output();
    }
    else printf("NO\n");
}

int main()
{
    init();
    solve();
    return 0;
}


