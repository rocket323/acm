#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#define MaxN 401
using namespace std;

struct Edge
{
	int idx;
	Edge * next;
}adj[MaxN], memo[60000];

int N, M, mset;
int cnt[MaxN], d[MaxN];
int Q[MaxN], sz;
int pq[MaxN];

void addEdge(int a, int b)
{
	Edge * ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
    memset(cnt, 0, sizeof cnt);
    memset(d, 0, sizeof d);
    scanf("%d%d", &N, &M);
    mset = 0;
    for(int i=0; i<=N; ++i) adj[i].next = NULL;
    
    for(int i=0; i<M; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        addEdge(b, a);
        d[a]++;
    }
}

void out()
{
    for(int i=sz-1; i>0; --i) printf("%d ", Q[i]);
    printf("%d\n", Q[0]);
}

int getMax()
{
	for(int i=N; i>=1; --i)
		if(d[i]==0) return i;
	return -1;
}

int solve()
{
    sz = 0;
    for(int i=1; i<=N; ++i)
    {
        int k = getMax();
        if(k==-1) return -1;
        Q[sz++] = k; d[k]--;
        for(Edge* ptr=adj[k].next; ptr; ptr=ptr->next)
        {
            d[ptr->idx]--;
        }
    }
    return 0;
}

int main()
{
	//freopen("3687.in", "r", stdin);
    int T;
    scanf("%d", &T);
    while(T--)
    {
        init();
        if(solve()==-1) printf("-1\n");
        else out();
    }
    //while(1);
    return 0;
}

