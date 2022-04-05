#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 1020
#define maxe 100010
#define INF 0x3f3f3f3f

struct Edge {
	int idx, flow;
	Edge *next, *opp;
}
adj[maxl], memo[maxe];

int n, m, s, t, Q[maxl], head, tail, mset, lv[maxl], a, b, c;

void addEdgeProcess(int a, int b, int c) {
	Edge * ptr = &memo[mset++];
	ptr->idx = b; ptr->flow = c; ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void addEdge(int a, int b, int c) {
	addEdgeProcess(a, b, c);
	addEdgeProcess(b, a, 0);
	adj[a].next->opp = &memo[mset - 1];
	adj[b].next->opp = &memo[mset - 2];
}

bool bfs(int s, int t) {
	memset(lv, -1, sizeof lv);
	head = tail = 0;
	lv[s] = 0;
	Q[tail++] = s;
	while(head < tail) {
		int u = Q[head++];
		for(Edge *ptr=adj[u].next; ptr; ptr=ptr->next) {
			int v = ptr->idx;
			if(lv[v] == -1 && ptr->flow) {
				lv[v] = lv[u] + 1;
				Q[tail++] = v;
			}
		}
	}
	return lv[t] != -1;
}

int dfs(int u, int flow) {
	if(u == t) return flow;
	int save = flow;
	for(Edge *ptr=adj[u].next; ptr; ptr=ptr->next) {
		int v = ptr->idx;
		if(lv[v] == lv[u] + 1 && ptr->flow) {
			int a = dfs(v, min(flow, ptr->flow));
			ptr->flow -= a;
			ptr->opp->flow += a;
			flow -= a;
		}
	}
	return save - flow;
}

int Dinic(int s, int t) {
	int flow = 0;
	while(bfs(s, t)) flow += dfs(s, INF);
	return flow;
}

int main() {
	while(scanf("%d%d", &m, &n) != EOF) {
		mset = 0;
		s = 1, t = n;
		for(int i=1; i<=n; ++i) adj[i].next = NULL;
		for(int i=0; i<m; ++i) {
			scanf("%d%d%d", &a, &b, &c);
			addEdge(a, b, c);
		}
		printf("%d\n", Dinic(1, n));
	}
	return 0;
}
