#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

struct node
{
	short r, c, br, bc;
	short pcnt, step;
	char path;
	node(short _r, short _c, short _br, short _bc, short _pcnt, short _step):
		r(_r), c(_c), br(_br), bc(_bc), pcnt(_pcnt), step(_step){}
};

struct cmp
{
	bool operator()(node A, node B)
	{
		return A.pcnt > B.pcnt || A.pcnt == B.pcnt && A.step > B.step;
	}
};

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
char dn[4] = {'n', 'e', 's', 'w'};
char dp[4] = {'N', 'E', 'S', 'W'};

int pr[21][21][21][21];
int pc[21][21][21][21];
int pbr[21][21][21][21];
int pbc[21][21][21][21];
char pn[21][21][21][21];

int pcnt[21][21][21][21];
int step[21][21][21][21];

priority_queue<node, vector<node>, cmp> pq;
int sr, sc, tr, tc, n, m, br, bc;
char G[30][30];

void init()
{
	for(int i=0; i<n; ++i)
	{
		scanf("%s", G[i]);
		for(int j=0; j<m; ++j)
		{
			if(G[i][j] == 'S') sr = i, sc = j;
			if(G[i][j] == 'B') br = i, bc = j;
			if(G[i][j] == 'T') tr = i, tc = j;
		}
	}
}

bool check(int r, int c)
{
	return (r >= 0 && r < n && c >= 0 && c < m && G[r][c] != '#');
}

void out(int _r, int _c, int _br, int _bc)
{
	if(_r == sr && _c == sc && _br == br && _bc == bc) return;
	out(pr[_r][_c][_br][_bc], pc[_r][_c][_br][_bc], pbr[_r][_c][_br][_bc], pbc[_r][_c][_br][_bc]);
	printf("%c", pn[_r][_c][_br][_bc]);
}

void solve()
{
	memset(pcnt, 0x3f, sizeof pcnt);
	memset(step, 0x3f, sizeof step);

	pcnt[sr][sc][br][bc] = step[sr][sc][br][bc] = 0;

	while(!pq.empty()) pq.pop();
	pq.push(node(sr, sc, br, bc, 0, 0));

	while(!pq.empty())
	{
		node now = pq.top();

		pq.pop();
		
		if(now.br == tr && now.bc == tc)
		{
			out(now.r, now.c, now.br, now.bc);
			puts("");
			return;
		}
		

		for(int k=0; k<4; ++k)
		{
			int _r = now.r + dr[k];
			int _c = now.c + dc[k];

			if(!check(_r, _c)) continue;

			if(_r == now.br && _c == now.bc)
			{
				int _br = now.br + dr[k];
				int _bc = now.bc + dc[k];
				if(!check(_br, _bc)) continue;

				if(now.pcnt+1 < pcnt[_r][_c][_br][_bc] || now.pcnt+1 == pcnt[_r][_c][_br][_bc] && now.step+1 < step[_r][_c][_br][_bc])
				{
					pq.push(node(_r, _c, _br, _bc, now.pcnt+1, now.step+1));

					pcnt[_r][_c][_br][_bc] = now.pcnt + 1;
					step[_r][_c][_br][_bc] = now.step + 1;


					pr[_r][_c][_br][_bc] = now.r;
					pc[_r][_c][_br][_bc] = now.c;
					pbr[_r][_c][_br][_bc] = now.br;
					pbc[_r][_c][_br][_bc] = now.bc;
					pn[_r][_c][_br][_bc] = dp[k];
				}
			}
			else
			{
				if(now.pcnt < pcnt[_r][_c][now.br][now.bc] || now.pcnt == pcnt[_r][_c][now.br][now.bc] && now.step+1 < step[_r][_c][now.br][now.bc])
				{
					pq.push(node(_r, _c, now.br, now.bc, now.pcnt, now.step+1));

					pcnt[_r][_c][now.br][now.bc] = now.pcnt;
					step[_r][_c][now.br][now.bc] = now.step + 1;

					pr[_r][_c][now.br][now.bc] = now.r;
					pc[_r][_c][now.br][now.bc] = now.c;
					pbr[_r][_c][now.br][now.bc] = now.br;
					pbc[_r][_c][now.br][now.bc] = now.bc;
					pn[_r][_c][now.br][now.bc] = dn[k];
				}
			}
		}
	}
	puts("Impossible.");
}

int main()
{
	int tc = 0;
	while(scanf("%d%d", &n, &m), n)
	{
		printf("Maze #%d\n", ++tc);
		init();
		solve();
		puts("");
	}
	return 0;
}

