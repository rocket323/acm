#include <iostream>
#include <algorithm>
#include <string>
#define MaxL 10010
using namespace std;

struct Edge
{
    int idx, len;
    Edge * next;
}adj[MaxL], memo[2*MaxL];

int n, K, ans, root;
int p[MaxL], mset;
int sz[MaxL], num;
int pre[MaxL];
int Q[MaxL], top;

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

int getCount(int l, int r, int sub)
{
    sort(Q+l, Q+r+1);

    int left=l, right=r;

    int ans = 0;
    while(left<=right)
    {
        while(left<=right && Q[left]+Q[right]-2*sub>K) right--;
        if(left<=right) ans += (right-left);
        left++;
    }
    return ans;
}

int dfs(int now, int father, int len)
{
    int ans = 0;

    int l=-1, r=-1;
    Edge * ptr = adj[now].next;

    l = top + 1;

    while(ptr)
    {
        int k = ptr->idx;
        int sl, sr;

        if(k==father){ ptr = ptr->next; continue; }
        sl = top + 1;

        ans += dfs(k, now, len + ptr->len);

        sr = r = top;

        ans -= getCount(sl, sr, len);
        ptr = ptr->next;
    }

    Q[++top] = len;
    r = top;

    ans += getCount(l, r, len);

    return ans;
}

int solve()
{
    ans = 0; top = 0;
    root = rand() % n + 1;
    //root = 1;
    ans = dfs(root, -1, 0);
    return ans;
}

int main()
{
    while(scanf("%d%d", &n, &K) && (n!=0||K!=0))
    {
        init();
        printf("%d\n", solve());
    }
    return 0;
}

