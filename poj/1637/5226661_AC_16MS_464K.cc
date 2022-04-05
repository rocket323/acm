#include <stdio.h>
#include <cstring>
#define MaxL 205
#define INF 0x7f7f7f7f
using namespace std;

struct Edge
{
	int idx, flow;
	Edge *next;
	Edge *opp;
}
adj[MaxL], memo[3000];

Edge *pre[MaxL];
int Q[MaxL], lt[MaxL], head, tail, mset, in[MaxL], out[MaxL];
int n, m, flag, s, t;
int checkflow;

void addEdgeProcess(int a, int b, int c)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b; ptr->flow = c;
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
	for(int i=0; i<=n+1; ++i) adj[i].next = NULL;
	memset(in, 0, sizeof in);
	memset(out, 0, sizeof out);
	scanf("%d%d", &n, &m);
	for(int i=0; i<m; ++i)
	{
		int a, b, t;
		scanf("%d%d%d", &a, &b, &t);
		out[a]++; in[b]++;
		if(t==0) addEdge(a, b, 1);
	}

	flag = 1;
	s = 0; t = n + 1;
	checkflow = 0;
	for(int i=1; i<=n; ++i)
	{
		int x = in[i] - out[i];
		if(x & 1){ flag = 0; return; }
		else if(x > 0){ addEdge(i, t, x/2); checkflow += x/2; }
		else if(x < 0) addEdge(s, i, -(x/2));
	}
}

bool bfs(int s, int t)
{
	memset(lt, -1, sizeof lt);
	tail = 1;
	Q[head = 0] = s; lt[s] = 1;
	for(int i=s; i<=t; ++i) pre[i] = NULL;

	while(head < tail)
	{
		int k = Q[head];
		Edge *ptr = adj[k].next;
		while(ptr)
		{
			if(lt[ptr->idx]==-1 && ptr->flow>0)
			{
				lt[ptr->idx] = 1;
				Q[tail++] = ptr->idx;
				pre[ptr->idx] = ptr;
				if(ptr->idx == t) return true;
			}
			ptr = ptr->next;
		}
		head++;
	}
	return lt[t] != -1;
}

int max_flow(int s, int t)
{
	int flow = 0;
	while(bfs(s, t))
	{
		int k = t;
		int Min = INF;
		while(k!=s)
		{
			if(Min > pre[k]->flow) Min = pre[k]->flow;
			k = pre[k]->opp->idx;
		}
		flow += Min;
		k = t;
		while(k!=s)
		{
			pre[k]->flow -= Min;
			pre[k]->opp->flow += Min;
			k = pre[k]->opp->idx;
		}
	}
	return flow;
}

void solve()
{
	if(!flag){ printf("impossible\n"); return; }
	int k = max_flow(s, t);
	if(k==checkflow) printf("possible\n");
	else printf("impossible\n");
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}
