#include <stdio.h>
#include <algorithm>
#include <queue>
#define INF 1000000000LL
#define ll long long
#define MaxL 50010
#include <iostream>
using namespace std;

struct Edge
{
	ll idx, w;
	Edge *next;
}
adj[MaxL], memo[2*MaxL];

struct Heap
{
	ll id, w;
	Heap(ll x, ll y):id(x), w(y){}
};

struct cmp
{
	bool operator()(Heap A, Heap B){ return A.w > B.w; }
};

ll n, m, mset;
ll v[MaxL], d[MaxL];
priority_queue<Heap, vector<Heap>, cmp> pq;

void addEdge(ll a, ll b, ll c)
{
	Edge* ptr = &memo[mset++];
	ptr->idx = b; ptr->w = c;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	while(!pq.empty()) pq.pop();
	scanf("%I64d%I64d", &n, &m);
	for(ll i=0; i<=n; ++i) adj[i].next = NULL;
	for(ll i=1; i<=n; ++i) scanf("%I64d", &v[i]);
	for(ll i=1; i<=m; ++i)
	{
		ll a, b, c;
		scanf("%I64d%I64d%I64d", &a, &b, &c);
		addEdge(a, b, c);
		addEdge(b, a, c);
	}
}

void dijkstra(ll s)
{
	for(ll i=0; i<=n; ++i) d[i] = INF;
	d[s] = 0;
	pq.push(Heap(s, 0));
	while(!pq.empty())
	{
		Heap now = pq.top();
		pq.pop();
		if(now.w > d[now.id]) continue;
		Edge * ptr = adj[now.id].next;
		while(ptr)
		{
			ll k = ptr->idx;
			if(d[now.id] + ptr->w < d[k])
			{
				d[k] = d[now.id] + ptr->w;
				pq.push(Heap(k, d[now.id] + ptr->w));
			}
			ptr = ptr->next;
		}
	}

}

void solve()
{
	dijkstra(1);
	ll ans = 0;
	for(ll i=1; i<=n; ++i) ans += (ll)d[i] * v[i];
	if(ans >= INF) printf("No Answer\n");
	else printf("%I64d\n", ans);
}

int main()
{
	ll t;
	scanf("%I64d", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}
