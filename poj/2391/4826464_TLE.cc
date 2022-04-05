#include <iostream>
#include <string>
#define MaxL 300
#define INF 1000000010
#define ll long long
using namespace std;

struct Edge
{
    ll idx, f;
    Edge * next, * opp;
}
adj[MaxL], memo[MaxL*MaxL];

Edge * pre[MaxL], * cur[MaxL];

ll sum, F, P, c[MaxL], f[MaxL];
ll g[MaxL][MaxL], mset;
ll lv[MaxL], Q[MaxL], top, Path[MaxL], head, tail, S, T;

ll Min(ll a, ll b){ return (a<b)?a:b; }

void init()
{
    scanf("%I64d%I64d", &F, &P);
    sum = 0;
    for(ll i=0; i<F; ++i){ scanf("%I64d%I64d", &c[i], &f[i]); sum += c[i]; }
    for(ll i=0; i<F; ++i)
        for(ll j=0; j<F; ++j)
            g[i][j] = INF;
    for(ll i=0; i<P; ++i)
    {
        ll a, b, c;
        scanf("%I64d%I64d%I64d", &a, &b, &c);
        a--; b--;
        if(c<g[a][b]) g[a][b] = g[b][a] = c;
    }

    for(ll k=0; k<F; ++k)
        for(ll i=0; i<F; ++i)
            for(ll j=0; j<F; ++j)
                if(g[i][k] + g[k][j] < g[i][j])
                    g[i][j] = g[i][k] + g[k][j];

    S = 2*F; T =S+1;
}

void addEdgeProcess(ll a, ll b, ll c)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->f = c;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void addEdge(ll a, ll b, ll c)
{
    addEdgeProcess(a, b, c);
    addEdgeProcess(b, a, 0);
    adj[a].next->opp = &memo[mset-1];
    adj[b].next->opp = &memo[mset-2];
}

void buildGraph(ll x)
{
    mset = 0;
    for(ll i=0; i<=T; ++i) adj[i].next = NULL;

    for(ll i=0; i<F; ++i)
        for(ll j=0; j<F; ++j)
            if(g[i][j]<=x) addEdge(i, j+F, c[i]);

    for(ll i=0; i<F; ++i) addEdge(S, i, c[i]);
    for(ll i=0; i<F; ++i) addEdge(i+F, T, f[i]);
}

bool bfs(ll S, ll T)
{
    memset(lv, -1, sizeof lv);
    Q[head=tail=1] = S;
    lv[S] = 1;
    while(head<=tail)
    {
        ll k = Q[head];
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

ll max_flow(ll S, ll T)
{
    ll u, flow = 0;
    while(bfs(S, T))
    {
        Path[top=1] = u = S;
        for(ll i=0; i<=T; ++i) cur[i] = adj[i].next;
        while(cur[S])
        {
            if(u!=T&&cur[u]&&cur[u]->f>0&&lv[cur[u]->idx]==lv[u]+1)
            {
                ll v = cur[u]->idx;
                Path[++top] = v;
                pre[v] = cur[u];
                u = v;
            }
            else if(u==T)
            {
                ll tmp = INF;
                for(ll i=top; i>1; --i) tmp = Min(tmp, pre[Path[i]]->f);
                for(ll i=top; i>1; --i)
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

bool check(ll x)
{
    buildGraph(x);
    if(max_flow(S, T) >= sum) return 1;
    else return 0;
}

void solve()
{
    ll l=0, r=INF, mid, ans = -1;

    while(l<=r)
    {
        mid = (l+r)>>1;
        if(check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    printf("%I64d\n", ans);
}

int main()
{
    init();
    solve();
    return 0;
}

