#include <iostream>
#define MaxN 2001
#define INF 1000000000
using namespace std;

struct Edge
{
    int idx, w;
    Edge * next;
};
Edge adj[MaxN], memo[40010];

struct node
{
    int idx, dis;
}H[400000];

int N, M, K, mset = 0;
int MAX = -1, len, vis[MaxN], d[MaxN];

void addEdge(int a, int b, int c)
{
    Edge *ptr = &memo[mset++];
    ptr->idx = b; ptr->w=c;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void init()
{
    int a, b, c;
    scanf("%d%d%d", &N, &M, &K);
    for(int i=1; i<=N; ++i) adj[i].next = NULL;

    for(int i=1; i<=M; ++i)
    {
        scanf("%d%d%d", &a, &b, &c);
        addEdge(a, b, c);
        addEdge(b, a, c);
        if(c>MAX) MAX = c;
    }
}

void swap(int a, int b)
{
    node tmp;
    tmp = H[a]; H[a] = H[b]; H[b] = tmp;
}

int pop()
{
    int i, j, k, t, ans;
    if(len==0) return -1;
    ans = H[1].idx;
    swap(1, len);
    len--;
    k = 1;
    while(k<len)
    {
        i=k<<1; j=i+1;
        if(i>len) break;
        if(j>len) t = i;
        else
        {
            if(H[i].dis<H[j].dis) t = i;
            else t = j;
        }
        if(H[t].dis<H[k].dis)
        {
            swap(t, k);
            k = t;
        }
        else break;
    }
    return ans;
}

void push(int s, int dis)
{
    int i,j,k, mid;
    len++;
    H[len].idx=s; H[len].dis=dis;
    k = len;
    while(k>1)
    {
        mid = k>>1;
        if(H[k].dis<H[mid].dis)
        {
            swap(k, mid);
            k = mid;
        }
        else break;
    }
}

int check(int num)
{
    int rec;
    len = 0;
    for(int i=1; i<=N; ++i) d[i] = INF;
    d[1] = 0;
    memset(vis, 0, sizeof vis);
    push(1, 0);
    for(int i=1; i<N; ++i)
    {
        while(true)
        {
            rec = pop();
            if(rec==-1) break;
            if(!vis[rec]) break;
        }
        vis[rec] = 1;

        Edge* ptr = adj[rec].next;
        while(ptr)
        {
            int k = ptr->idx;
            
            int w;
            if(ptr->w>num) w = 1;
            else w = 0;

            if(d[rec]+w<d[k])
            {
                d[k] = d[rec]+w;
                push(k, d[k]);
            }
            ptr = ptr->next;
        }
    }
    return d[N];
}

void solve()
{
    int l=0, r=MAX, mid, res = -1;

    while(l<=r)
    {
        mid = (l+r)>>1;
        int k = check(mid);
        if(k<=K)
        {
            res = mid;
            r = mid-1;
        }
        else l = mid+1;
    }
    printf("%d\n", res);
}

int main()
{
    init();
    solve();
    return 0;
}

