#include <stdio.h>
#include <cstring>
#include <sstream>
#define MaxL 1600
#define INF 0x7f7f7f7f
#define min(a,b) ((a<b)?a:b)
using namespace std;

struct Edge
{
	int idx, f;
	Edge *next, *opp;
}
adj[MaxL], memo[MaxL * 1000];

int n, m, mset, s, t;
int Q[MaxL], head, tail, lv[MaxL];
int P[MaxL], top;
Edge *pre[MaxL], *cur[MaxL];

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
	char S[50], T[100];
	int a;
	mset = 0;
	s = 0; t = n + m +1;
	for(int i=s; i<=t; ++i) adj[i].next = NULL;
	for(int i=1; i<=n; ++i)
	{
		gets(T);
		istringstream in(T);
		
		in >> S;
		while(in >> a)
		{
			addEdge(i, n+a+1, 1);
		}
	}
	for(int i=1; i<=n; ++i) addEdge(s, i, 1);
	for(int i=1; i<=m; ++i) addEdge(n+i, t, 1);
}

void make_Gra(int lim)
{
	for(Edge *ptr=adj[s].next; ptr; ptr=ptr->next)
	{
		ptr->f = 1;
		ptr->opp->f = 0;
	}
	for(int i=1; i<=n; ++i)
	{	
		for(Edge *ptr=adj[i].next; ptr; ptr=ptr->next)
		{
			if(ptr->idx==s) continue;
			ptr->f = 1;
			ptr->opp->f = 0;
		}
	}
	for(Edge *ptr=adj[t].next; ptr; ptr=ptr->next)
	{
		ptr->opp->f = lim;
		ptr->f = 0;
	}
}

bool bfs(int s, int t)
{
	memset(lv, -1, sizeof lv);
	lv[s] = 0;
	head = 0, tail = 1;
	Q[0] = s;
	
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
			if(u!=t && cur[u] && cur[u]->f && lv[cur[u]->idx]==lv[u]+1)
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
	int l = 0, r = n, mid, ans = -1;
	
	while(l <= r)
	{
		mid = (l + r) >> 1;
		make_Gra(mid);
		int k = Dinic(s, t);
		if(k==n)
		{
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}

	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d\n", &n, &m) && (n+m))
	{
		init();
		solve();
	}
	return 0;
}
