#include <stdio.h>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#define maxl 67010
#define TOT (2*n*(n+1))
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;

struct node
{
	ll st;
	int cost;
	node(ll _st, int _cost) : st(_st), cost(_cost) {}
};

struct cmp
{
	bool operator()(node A, node B)
	{
		return A.cost > B.cost;
	}
};

struct LIN
{
	int r1, c1, r2, c2;
}lin[maxl];

struct SQR
{
	int r1, c1, r2, c2;
}sqr[maxl];

int n, top, l, del[maxl], pre_cover;
bool cover[maxl];
vector<int> adj[maxl], list;
priority_queue<node, vector<node>, cmp> pq;

bool check(int a, int b)
{
	if(lin[a].r1 == lin[a].r2 && (lin[a].r1 == sqr[b].r1 || lin[a].r1 == sqr[b].r2))
	{
		return (sqr[b].c1 <= lin[a].c1 && lin[a].c2 <= sqr[b].c2);
	}
	else if(lin[a].c1 == lin[a].c2 && (lin[a].c1 == sqr[b].c1 || lin[a].c1 == sqr[b].c2))
	{
		return (sqr[b].r1 <= lin[a].r1 && lin[a].r2 <= sqr[b].r2);
	}
	return 0;
}

bool _less(int a, int b)
{
	int idx = 0;
	for(int i=0; i<adj[a].size(); ++i)
	{
		while(idx < adj[b].size() && adj[b][idx] != adj[a][i]) idx++;
		if(idx == adj[b].size()) return 0;
	}
	return 1;
}

void init()
{
	scanf("%d", &n);
	scanf("%d", &l);
	memset(del, 0, sizeof del);
	for(int i=0; i<l; ++i)
	{
		int a;
		scanf("%d", &a);
		del[a] = 1;
	}
	list.clear();
	for(int i=0; i<TOT; ++i) if(!del[i]) list.push_back(i);

	for(int i=0; i<2*n*(n+1); ++i)
	{
		int x = i;
		if(x >= (2 * n + 1) * n)
		{
			lin[i].r1 = lin[i].r2 = n;
			lin[i].c1 = x % (2 * n + 1);
			lin[i].c2 = lin[i].c1 + 1;
		}
		else
		{
			int mod = (2 * n + 1);
			if(x % mod < n)
			{
				lin[i].r1 = lin[i].r2 = x / mod;
				lin[i].c1 = x % mod;
				lin[i].c2 = lin[i].c1 + 1;
			}
			else
			{
				lin[i].c1 = lin[i].c2 = x % mod - n;
				lin[i].r1 = x / mod;
				lin[i].r2 = lin[i].r1 + 1;
			}
		}
	}

	top = 0;
	for(int r1=0; r1<=n; ++r1)
	for(int c1=0; c1<=n; ++c1)
	for(int len=1; len<=n && r1+len<=n && c1+len<=n; ++len)
	{
		int r2 = r1 + len, c2 = c1 + len;
		sqr[top].r1 = r1, sqr[top].c1 = c1;
		sqr[top].r2 = r2, sqr[top].c2 = c2;
		top++;
	}

	//printf("%d %d %d\n", n, TOT, top);

	for(int i=0; i<TOT; ++i)
	{
		adj[i].clear();
		for(int j=0; j<top; ++j)
		{
			if(check(i, j)) adj[i].push_back(j);
		}
		sort(adj[i].begin(), adj[i].end());
	}

	pre_cover = 0;
	memset(cover, 0, sizeof cover);
	for(int i=0; i<TOT; ++i) if(del[i])
	{
		for(int j=0; j<adj[i].size(); ++j)
		{
			if(!cover[adj[i][j]])
			{
				cover[adj[i][j]] = 1;
				pre_cover++;
			}
		}
	}

	for(int i=0; i<list.size(); ++i)
	{
		for(int j=0; j<top; ++j)
		{
			if(list[i] == j) continue;
			if(_less(list[i], j))
			{
				list[i] = list[list.size()-1];
				list.pop_back();
				break;
			}
		}
	}
}

int t_s[maxl], t_c;
bool vis[maxl];
vector<int> sz;
map<ll, int> mp;
map<ll, int> :: iterator it;
#define contain(x,y) (x & (1LL<<y))

void debug()
{
	/*
	for(int i=0; i<2*n*(n+1); ++i)
	{
		printf("%d %d %d %d %d\n", i, lin[i].r1, lin[i].c1, lin[i].r2, lin[i].c2);
	}

	puts("");
	
	for(int i=0; i<TOT; ++i)
	{
		printf("%d : ", i);
		for(int j=0; j<adj[i].size(); ++j)
		{
			printf("%d ", adj[i][j]);
		}
		puts("");
	}
	*/
}

int analyse(ll st, bool vis[])
{
	int ans= 0;
	for(int i=0; i<top; ++i) vis[i] = cover[i];

	for(int i=0; i<list.size(); ++i)
	{
		if(!contain(st, i)) continue;
		for(int j=0; j<adj[list[i]].size(); ++j)
		{
			int k = adj[list[i]][j];
			if(!vis[k]) vis[k] = 1;
		}
	}
	for(int i=0; i<top; ++i) ans += vis[i];
	return ans;
}

bool cmp2(int a, int b){ return a < b; }

int calc_exp(ll st, bool vis[])
{
	int left = top;
	for(int i=0; i<top; ++i) left -= vis[i];
	sz.clear();

	int save = left;

	return (save - 1 >= 0) ? save - 1 : 0;
	//printf("%d : ", left);

	for(int i=0; i<list.size(); ++i)
	{
		if(contain(st, i)) continue;
		int cnt = 0;
		//sz.push_back(adj[list[i]].size());
		for(int j=0; j<adj[list[i]].size(); ++j) if(!vis[adj[list[i]][j]]) cnt++;
		sz.push_back(cnt);
	}
	sort(sz.begin(), sz.end(), cmp2);
	int cnt = INF;
	for(int i=0; i<sz.size(); ++i)
	{
		left -= sz[i];
		if(left <= 0)
		{
			//printf("price : %d\n", i+1);
			cnt = i + 1;
			break;
		}
	}
	if(cnt < save - 3) cnt = save - 3;
	//printf("price : %d\n", INF);
	return cnt;
}

int a_search()
{
	while(!pq.empty()) pq.pop();
	mp.clear();
	memcpy(vis, cover, sizeof cover);
	mp.insert(make_pair(0, calc_exp(0, vis)));
	
	int k = calc_exp(0, vis);
	//if(k <= lim) pq.push(node(0, k));
	pq.push(node(0, k));

	while(!pq.empty())
	{
		node now = pq.top();
		pq.pop();

		int k = analyse(now.st, vis);

		//printf("%I64d %d %d\n", now.st, now.cost, k);

		if(k == top)
		{
			return now.cost;
		}

		int base = now.cost - calc_exp(now.st, vis);

		for(int i=0; i<list.size(); ++i)
		{
			if(contain(now.st, i)) continue;

			ll nst = now.st | (1LL<<i);
			analyse(nst, vis);
			int ncost = base + 1 + calc_exp(nst, vis);

			it = mp.find(nst);

			//if(ncost > lim) continue;

			if(it == mp.end())
			{
				pq.push(node(nst, ncost));
				mp.insert(make_pair(nst, ncost));
			}
			else if(ncost < it->second)
			{
				pq.push(node(nst, ncost));
				it->second = ncost;
			}
		}
	}
	return -1;
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		init();
		printf("%d\n", a_search());
		/*
		for(int i=0; ; ++i)
		{
			int k = a_search(i);
			//printf("%d %d\n", i, k);
			if(k != -1)
			{
				printf("%d\n", k);
				break;
			}
		}
		*/
	}
	return 0;
}

