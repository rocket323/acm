#include <stdio.h>
#include <cstring>
#define MaxL 100
#define INF 100000
#define min(a,b) ((a<b)?a:b)

struct Edge
{
	int idx, f;
	Edge *next, *opp;
}
adj[MaxL], memo[10000];

int s, n, m, k, b, t, mset;
int Q[MaxL], lv[MaxL], head, tail, P[MaxL], top;
Edge *cur[MaxL], *pre[MaxL];
char S[10];

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
	scanf("%d%d", &n, &t);
	s = n;
	mset = 0;
	for(int i=0; i<=s; ++i) adj[i].next = NULL;
	for(int i=0; i<n; ++i)
	{
		scanf("%s%d", S, &k);
		if(S[0]=='I') addEdge(s, i, INF);
		for(int j=0; j<k; ++j)
		{
			scanf("%d", &b);
			addEdge(i, b, INF);
			addEdge(b, i, 1);
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
	//if(lv[t]!=-1) printf("no\n");
	return lv[t]!=-1;
}

int Dicnic(int s, int t)
{
	int u, v, flow = 0;
	while(bfs(s, t))
	{
		for(int i=0; i<=s; ++i) cur[i] = adj[i].next;
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

void solve()
{
	int k = Dicnic(s, t);
	if(k >= INF) printf("PANIC ROOM BREACH\n");
	else printf("%d\n", k);
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
