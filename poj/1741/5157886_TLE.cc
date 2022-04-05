#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MaxL 10010
using namespace std;
#define Max(a,b) ((a>b)?a:b)

struct Edge
{
    int idx, len;
    Edge * next;
}adj[MaxL], memo[2*MaxL];

int n, K, ans, root;
int mset;
char vis[MaxL];
int Q[MaxL], top;
int lv[MaxL], sz;
int Size[MaxL];

void addEdge(int a, int b, int len)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->len = len;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void init()
{
    mset = 0;
    for(int i=0; i<=n; ++i) adj[i].next = NULL;
    for(int i=1; i<n; ++i)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        addEdge(a, b, c);
        addEdge(b, a, c);
    }
}

int getCount(int l, int r)
{
    sort(Q+l, Q+r+1);

    int left=l, right=r;

    int ans = 0;
    while(left<right)
    {
        while(left<right && Q[left]+Q[right]>K) right--;
        if(left<right) ans += (right-left);
        left++;
    }
    return ans;
}

void add_Q(int now, int len)
{
    vis[now] = 1;
    Q[++top] = len;
    for(Edge * ptr=adj[now].next; ptr; ptr=ptr->next)
    {
        int k = ptr->idx;
        if(!vis[k]) add_Q(k, len + ptr->len);
    }
    vis[now] = 0;
}

int handleSubTree(int now)
{

    int ans = 0;


    top = 0;

    for(Edge * ptr=adj[now].next; ptr; ptr=ptr->next)
    {
        int k = ptr->idx;
        if(vis[k]) continue;
        int sl;
        sl = top + 1;
        add_Q(k, ptr->len);
        ans -= getCount(sl, top);
    }


    Q[0] = 0;
    ans += getCount(0, top);
    return ans;
}

void dfs_for_root(int now)
{
    lv[++sz] = now;
    Size[now] = 1;
    vis[now] = 1;
   
    for(Edge * ptr=adj[now].next; ptr; ptr=ptr->next)
    {
        int k = ptr->idx;
        if(!vis[k])
        {
            dfs_for_root(k);
            Size[now] += Size[k];
        }
    }
    vis[now] = 0;
}

int chooseRoot(int now)
{
    sz = 0;
    dfs_for_root(now);

    int Min = n + 1;
    int ans = 0;

    
    for(int i=1; i<=sz; ++i)
    {
        int k = lv[i];
        int x = Max(Size[k]-1, sz - Size[k]);
        if(x <= Min)
        {
            Min = x;
            ans = k;
        }
    }
    
    return ans;
}

int dfs(int now)
{
    int root = chooseRoot(now);

    vis[root] = 1;
    int ans = handleSubTree(root);

    for(Edge * ptr=adj[root].next; ptr; ptr=ptr->next)
    {
        int k = ptr->idx;
        if(!vis[k]) ans += dfs(k);
    }

    return ans;
}

int solve()
{
    memset(vis, 0, sizeof vis);
    
    ans = dfs(1);
    return ans;
}

int main()
{
 
    while(scanf("%d%d", &n, &K) && n)
    {
        init();
        printf("%d\n", solve());
    }

    return 0;
}

