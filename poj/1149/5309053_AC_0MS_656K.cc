#include <stdio.h>
#include <cstring>
#define PIG 1101
#define MAN 111
#define INF 0x3f3f3f3f
#define min(a,b) ((a<b)?a:b)

struct Edge
{
    int idx, f;
    Edge *next, *opp;
}
adj[MAN], memo[PIG * MAN];

int pig[PIG], buy[MAN], S, T, mset;
int t[PIG], H[PIG][MAN], m, n;
int Q[MAN], head, tail, P[MAN], top, lv[MAN];
Edge *pre[MAN], *cur[MAN];

void addEdgeProcess(int a, int b, int c){
	Edge* ptr=&memo[mset++];
	ptr->idx=b; ptr->f=c;
	ptr->next=adj[a].next;
	adj[a].next=ptr;
}

void addEdge(int a, int b, int c){
	addEdgeProcess(a, b, c);
	addEdgeProcess(b, a, 0);
	adj[a].next->opp=&memo[mset-1];
	adj[b].next->opp=&memo[mset-2];
}

void init()
{
    scanf("%d%d", &m, &n);
    for(int i=1; i<=m; ++i) scanf("%d", &pig[i]);
    memset(t, 0, sizeof t);
    for(int i=1; i<=n; ++i)
    {
        int a, k, idx;
        scanf("%d", &k);
        for(int j=1; j<=k; ++j)
        {
            scanf("%d", &a);
            H[a][++t[a]] = i;
        }
        scanf("%d", &buy[i]);
    }
    S = 0, T = n + 1;
    mset = 0;
    for(int i=S; i<=T; ++i) adj[i].next = NULL;
    
    for(int i=1; i<=m; ++i)
    {
        if(t[i]==0) continue;
        addEdge(S, H[i][1], pig[i]);
    }
    for(int i=1; i<=n; ++i) addEdge(i, T, buy[i]);
    for(int i=1; i<=m; ++i)
    {
        for(int j=1; j<t[i]; ++j)
        {
            addEdge(H[i][j], H[i][j+1], INF);
        }
    }
}

bool bfs(int s, int t)
{
	memset(lv, -1, sizeof lv);
	lv[s] = 0; tail = 1; Q[head = 0] = s;
	
	while(head < tail)
	{
		int k = Q[head];
		for(Edge *ptr=adj[k].next; ptr; ptr=ptr->next)
		{
			if(ptr->f > 0 && lv[ptr->idx]==-1)
			{
				Q[tail++] = ptr->idx;
				lv[ptr->idx] = lv[k] + 1;
			}
		}
		head++;
	}
	return lv[t]!=-1;
}

int Dicnic(int s, int t)
{
	int u, v, flow = 0;
	while(bfs(s, t))
	{
		for(int i=s; i<=t; ++i) cur[i] = adj[i].next;
		P[top = 1] = u = s;
		while(cur[s])
		{
			if(u!=t && cur[u] && cur[u]->f>0 && lv[cur[u]->idx]==lv[u]+1)
			{
				int v = cur[u]->idx;
				P[++top] = v;
				pre[v] = cur[u];
				u = v;
			}
			else if(u==t)
			{
				int Min = INF;
				for(int i=top; i>1; --i) Min = min(Min, pre[P[i]]->f);
				for(int i=top; i>1; --i)
				{
					pre[P[i]]->f -= Min;
					pre[P[i]]->opp->f += Min;
					if(pre[P[i]]->f==0) top = i-1;
				}
				u = P[top];
				flow += Min;
			}
			else
			{
				while(u!=s && cur[u]==NULL) u = P[--top];
				cur[u] = cur[u]->next;
			}
		}
	}
	return flow;
}

int main()
{
    init();
    printf("%d\n", Dicnic(S, T));
    return 0;
}
