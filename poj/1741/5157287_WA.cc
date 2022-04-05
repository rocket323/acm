#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MaxL 10010
using namespace std;

struct Edge
{
    int idx, len;
    Edge * next;
}adj[MaxL], memo[2*MaxL];

int n, K, ans, root;
int p[MaxL], mset;
int vis[MaxL];
int pre[MaxL];
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
    while(left<=right)
    {
        while(left<=right && Q[left]+Q[right]>K) right--;
        if(left<=right) ans += (right-left);
        left++;
    }
    return ans;
}

void add_Q(int now, int len)
{
    vis[now] = 1;
    Q[++top] = len;
    Edge * ptr = adj[now].next;
    while(ptr)
    {
        int k = ptr->idx;
        if(!vis[k]) add_Q(k, len + ptr->len);
        ptr = ptr->next;
    }
    vis[now] = 0;
}

int handleSubTree(int now)
{

    int ans = 0;

    int l=-1, r=-1;
    Edge * ptr = adj[now].next;

    top = 0;
    l = top + 1;

    while(ptr)
    {
        int k = ptr->idx;
        int sl, sr;

        if(vis[k]){ ptr = ptr->next; continue; }
        sl = top + 1;

        add_Q(k, ptr->len);

        sr = r = top;

        ans -= getCount(sl, sr);
        ptr = ptr->next;
    }


    Q[++top] = 0;
    r = top;

    ans += getCount(l, r);

    return ans;
}

void dfs_for_root(int now)
{
    lv[++sz] = now;
    Size[now] = 1;
    vis[now] = 1;
    Edge * ptr = adj[now].next;
    while(ptr)
    {
        int k = ptr->idx;
        if(!vis[k])
        {
            dfs_for_root(k);
            Size[now] += Size[k];
        }
        ptr = ptr->next;
    }
    vis[now] = 0;
}

int Max(int a, int b){ return (a>b)?a:b; }

int chooseRoot(int now)
{
    sz = 0;
    dfs_for_root(now);

    int Min = 0x7f7f7f7f;
    int ans = -1;

    for(int i=1; i<=sz; ++i)
    {
        int k = lv[i];
        int x = Max(Size[k]-1, sz - Size[k]);
        if(x < Min)
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

    Edge * ptr = adj[root].next;
    while(ptr)
    {
        int k = ptr->idx;
        if(!vis[k]) ans += dfs(k);
        ptr = ptr->next;
    }

    return ans;
}

int solve()
{
    ans = 0; top = 0;
    memset(vis, 0, sizeof vis);

    
    ans = dfs(1);
    return ans;
}

int main()
{
    int t = 0;
    while(scanf("%d%d", &n, &K) && n)
    {
        t++;
        init();
        if(t > 6) break;
        printf("%d\n", solve());
    }
    return 0;
}

