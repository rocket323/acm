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
int ans, L[maxl], top;

template<typename Tnum>
inline void next_num(Tnum & ty) {
	ty = 0;
	char c;
	while(c = getchar(), (c < '0' || c > '9') && c != '-') if(c < 0) return;
	int f = 0;
	if(c == '-') f = 1, c = getchar();
	do
	{
		ty = ty * 10 + c - '0';
		c = getchar();
	}while(c >= '0' && c <= '9');
	if(f) ty -= ty;
}

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
		//scanf("%d%d", &a, &b);
		next_num(a);
		next_num(b);
		addEdge(a, b);
		addEdge(b, a);
	}
}

void solve()
{
	head = tail = 0;
	for(int i=1; i<=n; ++i) in[i] = vis[i] = 0;
	top = 0;
	for(int i=2; i<=n; ++i) L[top++] = i;
	vis[1] = 1;
	Q[tail++] = 1;

	ans = 0;
	while(head < tail) {
		int k = Q[head++];
		if(k != 1) ans++;

		for(Edge *ptr=adj[k].next; ptr; ptr=ptr->next) in[ptr->idx] = 1;
		for(int i=0; i<top; ++i) {
			int x = L[i];
			if(in[x]) continue;
			//vis[i] = 1;
			L[i] = L[top-1];
			top--;
			--i;
			Q[tail++] = x;
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
