#include <stdio.h>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#define INF 0x3f3f3f3f
using namespace std;

struct node
{
	int id;
	int cost;

	node(int _id, int _cost) : id(_id), cost(_cost) {}
};

struct cmp
{
	bool operator()(node A, node B)
	{
		return A.cost > B.cost;
	}
};

priority_queue<node, vector<node>, cmp> pq;

int dest, pre[400010], dir[400010], dist[400010];
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
char name[4] = {'u', 'r', 'd', 'l'};
int A[3][3], ta[3][3], tb[3][3], r, c;

int get_id(int A[3][3])
{
	int rank = 0, fac = 1, n = 9;
	for(int i=n-1; i>=0; --i)
	{
		int cnt = 0, x = A[i/3][i%3];
		for(int j=i+1; j<n; ++j) cnt += (A[j/3][j%3] < A[i/3][i%3]);
		rank += cnt * fac;
		fac *= (n - i);
	}
	return rank;
}

void decode(int k)
{
	int n = 9;
	int fac = 1, j, cnt, vis[10];
	for(int i=1; i<n; ++i) fac *= i;

	memset(vis, 0, sizeof vis);
	for(int i=0; i<n; ++i)
	{
		for(ta[i/3][i%3]=0; ta[i/3][i%3]<n; ++ta[i/3][i%3])
		{
			if(fac <= k) k -= fac;
			else break;
		}
		cnt = 0;
		for(j=0; ta[i/3][i%3]>=0; ++j) if(!vis[j]) ta[i/3][i%3]--;
		ta[i/3][i%3] = j - 1;
		vis[ta[i/3][i%3]] = 1;

		if(j - 1 == 0) r = i / 3, c = i % 3;

		if(i < n-1) fac /= (n - 1 - i);
	}
}

int get_cost(int A[3][3])
{
	int ans = 0;
	for(int i=0; i<3; ++i)
	{
		for(int j=0; j<3; ++j) if(A[i][j] != (i * 3 + j + 1) % 9) ans++;
	}
	return ans;
}

bool check(int r, int c){ return (r >= 0 && r < 3 && c >= 0 && c < 3); }
#define swap(a,b) a ^= b, b ^= a, a ^= b;

void output(int k)
{
	if(k == -1) return;
	output(pre[k]);
	if(pre[k] != -1) printf("%c", dir[k]);
}

void solve()
{
	memset(dist, 0x3f, sizeof dist);
	dist[get_id(A)] = get_cost(A);

	while(!pq.empty()) pq.pop();
	pq.push(node(get_id(A), get_cost(A)));

	memset(pre, -1, sizeof pre);
	while(!pq.empty())
	{
		node now = pq.top();
		pq.pop();

		if(now.id == dest)
		{
			output(dest);
			puts("");
			return;
		}

		decode(now.id);
		
		int base = now.cost - get_cost(ta);

		for(int k=0; k<4; ++k)
		{
			int rr = r + dr[k];
			int cc = c + dc[k];

			if(check(rr, cc))
			{
				swap(ta[r][c], ta[rr][cc]);
				int id = get_id(ta);
				int cost = base + 1 + get_cost(ta);

				if(cost < dist[id])
				{
					dist[id] = cost;
					pq.push(node(id, cost));
					pre[id] = now.id;
					dir[id] = name[k];
				}
				swap(ta[r][c], ta[rr][cc]);
			}
		}
	}

	puts("unsolvable");
}

int main()
{
	for(int i=0; i<3; ++i) for(int j=0; j<3; ++j) A[i][j] = (i * 3 + j + 1) % 9;
	dest = get_id(A);

	for(int i=0; i<3; ++i)
	{
		for(int j=0; j<3; ++j)
		{
			char str[3];
			scanf("%s", str);
			if(str[0] == 'x') A[i][j] = 0;
			else A[i][j] = str[0] - '0';
		}
	}

	solve();
	return 0;
}

