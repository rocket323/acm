#include <iostream>
#define MaxL 200000
#define LEN 700000
#define INF 100000000
using namespace std;

struct Edge
{
    int idx, w;
    Edge * next;
}
adj[3000], memo[MaxL];

int mset;
int N, M, S;
bool in[MaxL];
int Q[MaxL], head, tail, dist[MaxL], cnt[MaxL];

void addEdge(int a, int b, int c)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->w = c;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void init()
{
    S = N+1;

    mset = 0;
    for(int i=0; i<=S; ++i) adj[i].next = NULL;

    for(int i=0; i<M; ++i)
    {
        char ch;
        int a, b, c;
        scanf("%c", &ch);
        if(ch=='P')
        {
            scanf("%d%d%d", &a, &b, &c);
            getchar();
            addEdge(a, b, -c);
            addEdge(b, a, c);
        }
        else
        {
            scanf("%d%d", &a, &b);
            getchar();
            addEdge(a, b, -1);
        }
    }
    for(int i=1; i<=N; ++i) addEdge(S, i, 0);
}

void solve()
{
    for(int i=0; i<=S; ++i) dist[i] = INF;
    dist[S] = 0;
    memset(in, 0, sizeof in);
    memset(cnt, 0, sizeof cnt);
    in[S] = 1; cnt[S] = 1;
    head = 0;
    Q[tail = 1] = S;
    while(head!=tail)
    {
        head = (head + 1)%LEN;
        int k = Q[head];
        Edge * ptr = adj[k].next;
        while(ptr)
        {
            int v = ptr->idx;
            if(dist[k] + ptr->w < dist[v])
            {
                dist[v] = dist[k] + ptr->w;
                if(!in[v]){cnt[v] = cnt[k] + 1; in[v] = 1; tail = (tail+1)%LEN; Q[tail] = v; }
                if(cnt[v]>N+1){ printf("Unreliable\n"); return; }
            }
            ptr = ptr->next;
        }
        cnt[k]--;
        in[k] = 0;
    }
    printf("Reliable\n");
}

int main()
{
    while(scanf("%d%d", &N, &M)!=EOF)
    {
        getchar();
        init();
        solve();
    }
    return 0;
}

