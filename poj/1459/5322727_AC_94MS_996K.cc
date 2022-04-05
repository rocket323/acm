#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;
#define INF 0x3f3f3f3f
#define MaxL 201
#define min(a,b) ((a<b)?a:b)

struct Edge
{
	int idx, f;
	Edge *next, *opp;
}
adj[MaxL], memo[MaxL * MaxL * 2];

int a, b, c, n, np, nc, m;
char ch, S[100];
int Q[MaxL], head, tail, P[MaxL], top, lv[MaxL], mset, s, t;
Edge *pre[MaxL], *cur[MaxL];

void addEdgeProcess(int a, int b, int c)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b; ptr->f = c;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void addEdge(int a, int b, int c)
{
	addEdgeProcess(a, b, c);
	addEdgeProcess(b, a, 0);
	adj[a].next->opp = &memo[mset-1];
	adj[b].next->opp = &memo[mset-2];
}

void init()
{
	mset = 0;
	s = 0, t = n + 2;
	for(int i=s; i<=t; ++i) adj[i].next = NULL;
	for(int i=0; i<m; ++i)
	{
		scanf("%s", S);
		sscanf(S, "%c%d%c%d%c%d", &ch, &a, &ch, &b, &ch, &c);
		addEdge(a+1, b+1, c);
	}
	for(int i=0; i<np; ++i)
	{
		scanf("%s", S);
		sscanf(S, "%c%d%c%d", &ch, &a, &ch, &c);
		addEdge(s, a+1, c);
	}
	for(int i=0; i<nc; ++i)
	{
		scanf("%s", S);
		sscanf(S, "%c%d%c%d", &ch, &a, &ch, &c);
		addEdge(a+1, t, c);
	}
}

bool bfs(int s, int t)
{
	memset(lv, -1, sizeof lv);
	lv[s] = 0;
	Q[head = 0] = s; tail = 1;
	
	while(head < tail)
	{
		int k = Q[head];
		for(Edge *ptr=adj[k].next; ptr; ptr=ptr->next)
		{
			if(lv[ptr->idx]==-1 && ptr->f>0)
			{
				Q[tail++] = ptr->idx;
				lv[ptr->idx] = lv[k] + 1;
			}
		}
		++head;
	}
	return lv[t] != -1;
}

int Dinic(int s, int t)
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
				v = cur[u]->idx;
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
					if(pre[P[i]]->f==0) top = i - 1;
				}
				flow += Min;
				u = P[top];
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
	while(scanf("%d%d%d%d", &n, &np, &nc, &m)!=EOF)
	{
		init();
		printf("%d\n", Dinic(s, t));
	}
	return 0;
}
