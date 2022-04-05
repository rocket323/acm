#include <stdio.h>
#include <cstring>
#define maxl 10010
#define maxe 2000010

struct Edge
{
	int idx;
	Edge *next;
}
adj[maxl], memo[maxe];

int n, mset, m, a, b, in[maxl], vis[maxl], Q[maxl], head, tail;
int ans;

void addEdge(int a, int b)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=1; i<=n; ++i) adj[i].next = NULL;
	for(int i=0; i<m; ++i) {
		scanf("%d%d", &a, &b);
		addEdge(a, b);
		addEdge(b, a);
	}
}

void solve()
{
	head = tail = 0;
	for(int i=1; i<=n; ++i) in[i] = vis[i] = 0;
	vis[1] = 1;
	Q[tail++] = 1;

	ans = 0;
	while(head < tail) {
		int k = Q[head++];
		if(k != 1) ans++;

		for(Edge *ptr=adj[k].next; ptr; ptr=ptr->next) in[ptr->idx] = 1;
		for(int i=1; i<=n; ++i) {
			if(vis[i] || in[i]) continue;
			vis[i] = 1;
			Q[tail++] = i;
		}
		for(Edge *ptr=adj[k].next; ptr; ptr=ptr->next) in[ptr->idx] = 0;
	}

	printf("%d\n", ans);
}

int main()
{
	int tc = 0;
	while(scanf("%d%d", &n, &m), (n + m)) {
		init();
		printf("Case %d: ", ++tc);
		solve();
	}
	return 0;
}
