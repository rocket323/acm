#include <iostream>
using namespace std;

struct Edge
{
    int idx;
    Edge * next;
}adj[1001];

Edge memo[50000];
int N, K, mset;
int lv[1001];
int Q[2001], head, tail, pre[1001];

void addEdge(int a, int b)
{
    Edge * ptr = &memo[mset++];
    ptr->idx = b;
    ptr->next = adj[a].next;
    adj[a].next = ptr;
}

void init()
{
    scanf("%d%d", &N, &K);
    for(int i=0; i<=K; ++i)
        adj[i].next = NULL;
    mset = 0;
    for(int i=1; i<=N; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        addEdge(a, b);
    }
}

void bfs()
{
    Q[head=tail=1] = 1;
    lv[1] = 0;
    while(head<=tail)
    {
        int k = Q[head];
        Edge * ptr = adj[k].next;
        while(ptr)
        {
            int tmp = ptr->idx;
            if(lv[tmp]==-1)
            {
                lv[tmp] = lv[k]+1;
                pre[tmp] = k;
                Q[++tail] = tmp;
            }
            ptr = ptr->next;
        }
        head++;
    }
}

void output()
{
    head = 0;
    int now = K;
    while(true)
    {
        Q[++head] = now;
        if(now==1) break;
        now = pre[now];
    }
    printf("%d\n", head);
    for(int i=head; i>=1; --i)
        printf("%d\n", Q[i]);
}

void process()
{
    memset(lv, -1, sizeof lv);
    memset(pre, 0, sizeof pre);
    bfs();
    if(lv[K]==-1)
        printf("-1\n");
    else output();
}

int main()
{
    init();
    process();
    return 0;
}
