#include <iostream>
#define MaxL 200
#define UNVIS 0
#define VIS 1
#define OVER 2
using namespace std;

struct Edge
{
    int idx;
    Edge * next;
}
adj2[MaxL], adj[MaxL], memo[1000000];

int N, M, pre[MaxL];

int mark[MaxL], low[MaxL], id[MaxL];
int st[MaxL], top;

int col[MaxL], in[MaxL];
int mset, S[MaxL], sz, tt;
char ans[MaxL];
int gil;
bool success;

int opp(int x){ return (x<N)?x+N:x-N; }

void addEdge(Edge& adj, int a, int b)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->next = adj.next;
    adj.next = ptr;
}

void init()
{
    char s1[20], s2[20];
    int a, b, j;

    gil = -1;

    mset = 0;
    for(int i=0; i<2*N; ++i) adj[i].next = NULL;
    memset(in, 0, sizeof in);

    for(int i=0; i<M; ++i)
    {
        cin>>s1>>s2;
        a = 0;
        for(j=0; j<strlen(s1)-1; ++j) a = a*10 + s1[j] - '0';
        if(s1[j]=='w') a += N;
        b = 0;
        for(j=0; j<strlen(s2)-1; ++j) b = b*10 + s2[j] - '0';
        if(s2[j]=='w') b += N;


        addEdge(adj[opp(b)], opp(b), a); //反向建图
        addEdge(adj[opp(a)], opp(a), b);
    }

    addEdge(adj[0], 0, N);
    addEdge(adj[0], 0, 0);

}

void buildGraph()
{

    for(int i=0; i<2*N; ++i) adj2[i].next = NULL;

    for(int i=0; i<2*N; ++i)
    {
        Edge * ptr = adj[i].next;
        while(ptr)
        {
            addEdge(adj2[pre[i]], pre[i], pre[ptr->idx]);
            in[pre[ptr->idx]]++;
            ptr = ptr->next;
        }
    }
}

void dfs(int now, int color)
{
    col[now] = color;
    Edge * ptr = adj2[now].next;
    while(ptr)
    {
        if(col[ptr->idx]==-1) dfs(ptr->idx, color);
        ptr = ptr->next;
    }
}

void construct()
{
    memset(col, -1, sizeof col);
    sz = 0;
    for(int i=0; i<2*N; ++i)
    {
        if(pre[i]!=i||in[i]!=0) continue;
        S[sz++] = i;
    }
    for(int i=0; i<2*N; ++i)
    {
        if(pre[i]!=i) continue;
        
        if(sz==0)
        {
            printf("bad luck\n");
            success = 0;
            return;
        }
        
        int k = S[--sz];
        if(col[k]==-1)
        {
                col[k] = 1;
                dfs(opp(k), 2);
        }
        Edge * ptr = adj2[k].next;
        while(ptr)
        {
            in[ptr->idx]--;
            if(in[ptr->idx]==0) S[sz++] = ptr->idx;
            ptr = ptr->next;
        }
    }
}

void output()
{
    for(int i=1; i<N; ++i)
        if(col[pre[i]] == col[pre[N]]) ans[i] = 'h';
        else ans[i] = 'w';
    for(int i=1; i<N-1; ++i) printf("%d%c ", i, ans[i]);
    printf("%d%c\n", N-1, ans[N-1]);
}

void SCC(int now)
{
    mark[now] = VIS;
    low[now] = id[now] = ++tt;
    st[++top] = now;
    
    Edge * ptr = adj[now].next;
    while(ptr)
    {
        int k = ptr->idx;
        if(mark[k]==UNVIS)
        {
            SCC(k);
            if(low[k]<low[now]) low[now] = low[k];
        }
        else if(mark[k]==VIS)
        {
            if(low[k]<low[now]) low[now] = low[k];
        }
        ptr = ptr->next;
    }
    if(low[now]==id[now])
    {
        do
        {
            mark[st[top]] = OVER;
            pre[st[top]] = now;
        }while(st[top--]!=now);
    }
}

void solve()
{
    for(int i=0; i<2*N; ++i) pre[i] = i;

    top = 0; tt = 0;
    memset(mark, 0, sizeof mark);
    for(int i=0; i<2*N; ++i)
        if(mark[i]==UNVIS) SCC(i);

    for(int i=0; i<N; ++i)
    {
        if(pre[i]==pre[i+N])
        {
            printf("bad luck\n");
            return;
        }
    }

    /*for(int i=0; i<2*N; ++i)
    {
        cout<<i<<" : ";
        Edge * ptr = adj[i].next;
        while(ptr)
        {
            cout<<ptr->idx<<' ';
            ptr = ptr->next;
        }
        cout<<endl;
    }
    */
    
    gil = pre[N];
    success = 1;

    buildGraph();
    construct();
    //for(int i=0; i<2*N; ++i) cout<<col[pre[i]]<<' '; cout<<endl;
    if(success) output();
}

int main()
{
    while((cin>>N>>M) && N)
    {
        init();
        solve();
    }
    return 0;
}

