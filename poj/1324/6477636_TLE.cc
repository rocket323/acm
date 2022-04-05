#include <stdio.h>
#include <cstring>
#include <map>
#include <queue>
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

priority_queue<node, vector<node>, cmp> pq;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int n, m, l, start, tr[10], tc[10];
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

void init()
{

	mask = (1<<(l-1));
	mask *= 400;

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

void solve()
{
	while(!pq.empty()) pq.pop();
	mp.clear();

	pq.push(node(start, sr[0] + sc[0]));
	mp.insert(make_pair(start, sr[0] + sc[0]));

	while(!pq.empty())
	{
		node now = pq.top();
		pq.pop();

		decode(now.state, sr, sc);
		if(sr[0] == 0 && sc[0] == 0)
		{
			printf("%d\n", now.cost);
			return;
		}

		int base = now.cost - (sr[0] + sc[0]);

		for(int k=0; k<4; ++k)
		{
			int _r = sr[0] + dr[k];
			int _c = sc[0] + dc[k];
			if(!check(_r, _c, sr, sc)) continue;

			for(int i=l-1; i>0; --i)
			{
				tr[i] = sr[i-1], tc[i] = sc[i-1];
			}

			tr[0] = _r, tc[0] = _c;
			int _state = encode(tr, tc);
			int _cost = base + 1 + tr[0] + tc[0];

			it = mp.find(_state);
			if(it == mp.end())
			{
				mp.insert(make_pair(_state, _cost));
				pq.push(node(_state, _cost));
			}
			else if(_cost < it->second)
			{
				it->second = _cost;
				pq.push(node(_state, _cost));
			}
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

