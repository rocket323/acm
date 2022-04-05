#include <stdio.h>
#include <cstring>
#define MaxL 211

struct node
{
	int r, c, d;
}
Q[MaxL * MaxL];

int dr[4] = {0, -1, 0, 1};
int dc[4] = {1, 0, -1, 0};
int n, a[MaxL][MaxL], b[MaxL][MaxL], p[MaxL*MaxL], dist[MaxL][MaxL];
int head, tail, pl;

void push(int r, int c, int d)
{
	dist[r][c] = d;
	Q[tail].r = r;
	Q[tail].c = c;
	Q[tail].d = d;
	tail++;
}

void init()
{
	memset(dist, 0x7f, sizeof dist);
	head = tail = pl = 0;
	p[0] = 0;
	scanf("%d", &n);
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			scanf("%d", &a[i][j]);
			if(a[i][j] != 0)
			{
				++pl; p[pl] = a[i][j];
				push(i, j, 0);
				b[i][j] = pl;
			}
		}
	}
}

void solve()
{
	while(head < tail)
	{
		int r = Q[head].r, c = Q[head].c, d = Q[head].d;

		for(int k=0; k<4; ++k)
		{
			int rr = r + dr[k];
			int cc = c + dc[k];
			if(rr<0 || rr==n || cc<0 || cc==n) continue;

			if(dist[rr][cc] > d + 1)
			{
				push(rr, cc, d + 1);
				b[rr][cc] = b[r][c];
			}
			else if(dist[rr][cc]==d+1 && b[rr][cc]!=b[r][c]) b[rr][cc] = 0;
		}
		++head;
	}

	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<n-1; ++j) printf("%d ", p[b[i][j]]);
		printf("%d\n", p[b[i][n-1]]);

	}
}

int main()
{
	init();
	solve();
	return 0;
}