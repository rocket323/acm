#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define MaxL 16100
#define max(a,b) ((a>b)?a:b)
#define INF 0x7f7f7f7f

struct node
{
	int l, p, s;
}
E[101];

int f[2][MaxL];
int n, m, head, tail, Q[MaxL];

bool cmp(node A, node B)
{
	return A.s < B.s;
}

void init()
{
	for(int i=1; i<=n; ++i) scanf("%d%d%d", &E[i].l, &E[i].p, &E[i].s);
	sort(E+1, E+1+n, cmp);
}

int fun(int now, int idx, int i)
{
	return f[now^1][idx] - E[i].p * idx;
}

void solve()
{
	memset(f, 0x80, sizeof f);
	for(int i=0; i<=m; ++i) f[0][i] = 0;

	int ans = 0, idx, now = 0;

	for(int i=1; i<=n; ++i)
	{
		now ^= 1;
		
		for(int j=0; j<=m; ++j) f[now][j] = f[now^1][j];

		head = tail = idx = 0;
		for(int j=E[i].s; j<=E[i].s+E[i].l-1 && j<=m; ++j)
		{
			f[now][j] = max(f[now][j], f[now][j-1]);

			while(idx<E[i].s)
			{
				while(head < tail && fun(now, Q[tail-1], i) <= fun(now, idx, i)) tail--;
				if(f[now^1][idx] > -INF) Q[tail++] = idx;
				idx++;
			}

			while(head < tail && j-Q[head] > E[i].l) head++;

			if(head < tail)
			{
				int k = Q[head];
				f[now][j] = max(f[now][j], f[now^1][k] - E[i].p * k + E[i].p * j);
			}

		}

		for(int j=1; j<=m; ++j) f[now][j] = max(f[now][j], f[now][j-1]);
	}

	printf("%d\n", f[now][m]);
}

int main()
{
	while(scanf("%d%d\n", &m, &n) != EOF)
	{
		init();
		solve();
	}
	return 0;
}
