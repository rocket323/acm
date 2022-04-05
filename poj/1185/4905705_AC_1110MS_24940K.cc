#include <iostream>
#define MaxL 60000
using namespace std;

struct Edge
{
    int idx, num;
    Edge * next;
}
adj[MaxL], memo[10*MaxL];

int n, m, mset, sz, p[12];
int a[11][2], b[11][2];
char S[101][11];
int f[101][MaxL];
int ST[60000], top;

void init()
{
    cin >> n >> m;
    for(int i=1; i<=n; ++i)
    {
        for(int j=1; j<=m; ++j)
            cin >> S[i][j];
    }
    p[0] = 1;

    for(int i=1; i<=m; ++i) p[i] = p[i-1] * 3;
}

void addEdge(int a, int b, int c)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b; ptr->num = c;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

int getID(int b[][2])
{
    int id = 0, k;
    for(int i=m; i>=1; --i)
    {
        if(b[i][0]==0 && b[i][1]==0) k = 0;
        if(b[i][0]==1 && b[i][1]==0) k = 1;
        if(b[i][0]==0 && b[i][1]==1) k = 2;
        id = id * 3 + k;
    }
    return id;
}

void dfs(int pos, int now, int a[][2], int b[][2], int num)
{

    if(pos > m)
    {
        int k = getID(b);
        addEdge(now, k, num);
        return;
    }

    dfs(pos+1, now, a, b, num);
    
    if(!a[pos][0] && !a[pos][1])
    {
        b[pos][0] = 1;
        dfs(pos+3, now, a, b, num+1);
        b[pos][0] = 0;
    }
}

void toArray(int now)
{
    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
    int pos = 1;
    while(now)
    {
        int k = now % 3;
        if(k==1){ b[pos][1] = a[pos][0] = 1; }
        else if(k==2){ a[pos][1] = 1; }
        now /= 3;
        pos++;
    }
}

int check(int r, int now)
{
    int pos = 1;
    while(now)
    {
        int k = now % 3;
        if(S[r][pos]=='H' && k==1) return 0;
        now /= 3; pos++;
    }
    return 1;
}

void dp()
{
    memset(f, -1, sizeof f);
    f[0][0] = 0;

    int ans = 0;
    for(int i=0; i<=n; ++i)
    {
        for(int p=1; p<=top; ++p)
        {
            int j = ST[p];
            if(f[i][j]==-1) continue;
                Edge * ptr= adj[j].next;
            if(i < n)
            {
                while(ptr)
                {
                    int k = ptr->idx;
                    if(check(i+1, k) && f[i][j] + ptr->num > f[i+1][k])
                        f[i+1][k] = f[i][j] + ptr->num;
                    ptr = ptr->next;
                }
            }
            else if(f[i][j] > ans) ans = f[i][j];
        }
    }
    printf("%d\n", ans);
}

void dfs2(int pos, int b[][2])
{

    if(pos==m+1)
    {
        int k = getID(b);
        ST[++top] = k;
        return;
    }

    dfs2(pos+1, b);

    if( (pos<=1 || !b[pos-1][0]) && (pos<=2 || !b[pos-2][0]) )
    {
        b[pos][0] = 1;
        dfs2(pos+1, b);
        b[pos][0] = 0;
    }
    if( (pos<=1 || !b[pos-1][1]) && (pos<=2 || !b[pos-2][1]) )
    {
        b[pos][1] = 1;
        dfs2(pos+1, b);
        b[pos][1] = 0;
    }
}

void solve()
{

    top = 0;
    memset(b, 0, sizeof b);
    dfs2(1, b);
    
    sz = p[m];
    for(int p=1; p<=top; ++p)
    {
        int i = ST[p];
        toArray(i);
        dfs(1, i, a, b, 0);
    }

    dp();
}

int main()
{
    init();
    solve();
    return 0;
}

