/*
 * =======================================================
 *       Filename:  3228.cpp
 *    Description:  
 *        Created:  25/10/10 22:51:48
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#define maxl 300
#define maxe 300010

//////////////////////////////////////////////////////
#define MaxL 240
#define MaxE (MaxL*MaxL*4)
#define INF 0x3f3f3f3f

struct Edge
{
	int idx, flow;
	Edge *next, *opp;
}
adj[MaxL], memo[MaxE];

int mset, Q[MaxL], head, tail, lv[MaxL], P[MaxL], top;
int s, t, sum, ea[maxe], eb[maxe], ec[maxe], w[maxl], g[maxl], n, m, mlen;
Edge *pre[MaxL], *cur[MaxL];

void clear(){ mset = 0; for(int i=0; i<MaxL; ++i) adj[i].next = NULL; }

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

bool bfs(int s, int t)
{
	memset(lv, -1, sizeof lv);
	tail = 1;
	Q[head = 0] = s; lv[s] = 0;
	while(head < tail)
	{
		int k = Q[head];
		for(Edge *ptr=adj[k].next; ptr; ptr=ptr->next)
		{
			if(ptr->flow && lv[ptr->idx]==-1)
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
	int flow = 0, u;
	while(bfs(s, t))
	{
		P[top = 1] = u = s;
		for(int i=s; i<=t; ++i) cur[i] = adj[i].next;
		while(cur[s])
		{
			if(u!=t && cur[u] && cur[u]->flow && lv[cur[u]->idx]==lv[u]+1)
			{
				int v = cur[u]->idx;
				P[++top] = v;
				pre[v] = cur[u];
				u = v;
			}
			else if(u==t)
			{
				int Min = INF;
				for(int i=top; i>1; --i) if(pre[P[i]]->flow < Min) Min = pre[P[i]]->flow;
				for(int i=top; i>1; --i)
				{
					pre[P[i]]->flow -= Min;
					pre[P[i]]->opp->flow += Min;
					if(pre[P[i]]->flow==0) top = i - 1;
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
//////////////////////////////////////////////////////

void init()
{
	sum = 0;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &g[i]);
		sum += g[i];
	}
	for(int i=1; i<=n; ++i) scanf("%d", &w[i]);

	scanf("%d", &m);
	mlen = 0;
	for(int i=0; i<m; ++i)
	{
		scanf("%d%d%d", &ea[i], &eb[i], &ec[i]);
		if(mlen < ec[i]) mlen = ec[i];
	}
}

bool check(int limit)
{
	mset = 0;
	for(int i=1; i<=n; ++i) adj[i].next = NULL;
	for(int i=0; i<m; ++i)
	{
		if(ec[i] > limit) continue;
		addEdge(ea[i], eb[i], INF);
		addEdge(eb[i], ea[i], INF);
	}
	s = 0, t = n + 1;
	for(int i=1; i<=n; ++i)
	{
		if(g[i]) addEdge(s, i, g[i]);
		if(w[i]) addEdge(i, t, w[i]);
	}

	int k = Dinic(s, t);
	return k == sum;
}

void solve()
{
	int l = 0, r = mlen, mid, ans;
	while(l <= r)
	{
		mid = (l + r) / 2;
		if(check(mid))
		{
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	if(ans == -1) puts("No Solution");
	else printf("%d\n", ans);
}

int main()
{
	while(scanf("%d", &n), n)
	{
		init();
		solve();
	}
	return 0;
}

