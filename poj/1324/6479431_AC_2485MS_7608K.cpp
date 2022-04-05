#include <stdio.h>
#include <cstring>
#include <map>
#include <queue>
#define INF 0x3f3f3f3f
#define Prime ((1<<17)-1)
#define Size 6553700
#include <algorithm>
using namespace std;

struct node
{
	int state, cost;
	node(int _state, int _cost) : state(_state), cost(_cost) {}
};

struct cmp
{
	bool operator()(node A, node B)
	{
		return A.cost > B.cost;
	}
};

queue<node> pq;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

bool vis[6553610];

int Q[100000], head, tail;
int n, m, l, start, tr[10], tc[10], dist[20][20];
int sr[10], sc[10], G[20][20], stones, mask;
map<int, int> mp;
map<int, int> :: iterator it;

int get_dir(int r1, int c1, int r2, int c2)
{
	if(c1 == c2 && r2 == r1 - 1) return 0;
	if(c1 == c2 && r2 == r1 + 1) return 2;
	if(r1 == r2 && c2 == c1 + 1) return 1;
	if(r1 == r2 && c2 == c1 - 1) return 3;
	return -1;
}

int encode(int sr[], int sc[])
{
	int start = 0;
	for(int i=0; i<l; ++i)
	{
		if(i == 0)
		{
			start = start * 20 + sr[i];
			start = start * 20 + sc[i];
		}
		else
		{
			int k = get_dir(sr[i-1], sc[i-1], sr[i], sc[i]);
			start = start * 4 + k;
		}
	}
	return start;
}

void decode(int state, int sr[], int sc[])
{
	int d[10];
	for(int i=l-1; i>0; --i)
	{
		d[i] = state % 4;
		state /= 4;
	}
	sc[0] = state % 20;
	sr[0] = state / 20 % 20;

	for(int i=1; i<l; ++i)
	{
		sr[i] = sr[i-1] + dr[d[i]];
		sc[i] = sc[i-1] + dc[d[i]];
	}
}

void bfs()
{
	memset(dist, 0x3f, sizeof dist);
	dist[0][0] = 0;
	tail = 1;
	Q[head = 0] = 0;

	while(head < tail)
	{
		int r = Q[head] / 20;
		int c = Q[head] % 20;
		for(int k=0; k<4; ++k)
		{
			int _r = r + dr[k];
			int _c = c + dc[k];
			if(_r < 0 || _r == n || _c < 0 || _c == m || G[_r][_c]) continue;
			if(dist[r][c] + 1 < dist[_r][_c])
			{
				dist[_r][_c] = dist[r][c] + 1;
				Q[tail++] = _r * 20 + _c;
			}
		}
		++head;
	}
}

void init()
{
	for(int i=0; i<l; ++i)
	{
		scanf("%d%d", &sr[i], &sc[i]);
		sr[i]--, sc[i]--;
	}
	start = encode(sr, sc);

	scanf("%d", &stones);
	memset(G, 0, sizeof G);
	int r, c;
	for(int i=0; i<stones; ++i)
	{
		scanf("%d%d", &r, &c);
		G[r-1][c-1] = 1;
	}
}

bool check(int r, int c, int sr[], int sc[])
{
	if(r < 0 || r == n || c < 0 || c == m) return 0;
	if(G[r][c]) return 0;
	for(int i=1; i<l; ++i) if(r == sr[i] && c == sc[i]) return 0;
	return 1;
}

int get_cost(int r, int c)
{
	return dist[r][c];
}

void solve()
{
	while(!pq.empty()) pq.pop();
	memset(vis, 0, sizeof vis);

	pq.push(node(start, 0));
	vis[start] = 1;

	while(!pq.empty())
	{
		node now = pq.front();
		pq.pop();

		decode(now.state, sr, sc);
		if(sr[0] == 0 && sc[0] == 0)
		{
			printf("%d\n", now.cost);
			return;
		}

		for(int i=l-1; i>0; --i)
		{
			tr[i] = sr[i-1], tc[i] = sc[i-1];
		}

		for(int k=0; k<4; ++k)
		{
			int _r = sr[0] + dr[k];
			int _c = sc[0] + dc[k];
			if(!check(_r, _c, sr, sc)) continue;


			tr[0] = _r, tc[0] = _c;
			int _state = encode(tr, tc);

			if(vis[_state]) continue;

			vis[_state] = 1;
			pq.push(node(_state, now.cost + 1));

		}
	}
	printf("%d\n", -1);
}

int main()
{
	int tc = 0;
	while(scanf("%d%d%d", &n, &m, &l), (n+m+l))
	{
		printf("Case %d: ", ++tc);
		init();
		solve();
	}
	return 0;
}

