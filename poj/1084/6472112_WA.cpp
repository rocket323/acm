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

int n, top, l, del[maxl], pre_cover, cnt[maxl], left, flag;
int vis_line[maxl], vis_sqr[maxl], bak_sqr[maxl];
vector<int> adj_line[maxl], adj_sqr[maxl], list;

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

	for(int i=0; i<TOT; ++i)
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

	for(int i=0; i<top; ++i) adj_sqr[i].clear();
	for(int i=0; i<list.size(); ++i) adj_line[i].clear();
	for(int i=0; i<list.size(); ++i)
	{
		for(int j=0; j<top; ++j)
		{
			if(check(list[i], j))
			{
				adj_line[i].push_back(j);
				adj_sqr[j].push_back(i);
			}
		}
	}

	memset(vis_sqr, 0, sizeof vis_sqr);
	memset(vis_line, 0, sizeof vis_line);
	left = top;
	for(int i=0; i<TOT; ++i)
	{
		if(!del[i]) continue;
		for(int j=0; j<top; ++j) if(check(i, j))
		{
			vis_sqr[j]++;
			if(vis_sqr[j] == 1) left--;
		}
	}
	memcpy(bak_sqr, vis_sqr, sizeof vis_sqr);
}

void dfs(int left, int limit, int cost)
{
	if(flag) return;
	if(cost > limit) return;
	//if(cost + calc_exp() >= limit) return;
	if(left == 0)
	{
		flag = 1;
		return;
	}

	int k = -1;
	for(int i=top-1; i>=0; --i)
	{
		if(!vis_sqr[i])
		{
			k = i;
			break;
		}
	}

	for(int i=0; i<adj_sqr[k].size(); ++i)
	{
		int x = adj_sqr[k][i], add = 0;
		for(int j=0; j<adj_line[x].size(); ++j)
		{
			int sqrid = adj_line[x][j];
			vis_sqr[sqrid]++;
			if(vis_sqr[sqrid] == 1) add++;
		}

		dfs(left - add, limit, cost + 1);

		if(flag) return;

		for(int j=0; j<adj_line[x].size(); ++j)
		{
			int sqrid = adj_line[x][j];
			vis_sqr[sqrid]--;
		}
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		init();

		for(int i=0; ; ++i)
		{
			memcpy(vis_sqr, bak_sqr, sizeof bak_sqr);
			memset(vis_line, 0, sizeof vis_line);
			flag = 0;
			dfs(left, i, 0);
			if(flag)
			{
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}

