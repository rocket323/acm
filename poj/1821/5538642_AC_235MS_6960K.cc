
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

int f[101][MaxL];
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

int fun(int i, int idx)
{
	return f[i-1][idx] - E[i].p * idx;
}

void solve()
{
	memset(f, 0x80, sizeof f);
	for(int i=0; i<=m; ++i) f[0][i] = 0;

	int ans = 0, idx;

	for(int i=1; i<=n; ++i)
	{
		
		for(int j=0; j<=m; ++j) f[i][j] = f[i-1][j];

		head = tail = idx = 0;
		for(int j=E[i].s; j<=E[i].s+E[i].l-1 && j<=m; ++j)
		{
			if(i<n) f[i][j] = max(f[i][j], f[i][j-1]);

			while(idx<E[i].s)
			{
				while(head < tail && fun(i, Q[tail-1]) <= fun(i, idx)) tail--;
				if(f[i-1][idx] > -INF) Q[tail++] = idx;
				idx++;
			}

			while(head < tail && j-Q[head] > E[i].l) head++;

			if(head < tail)
			{
				int k = Q[head];
				f[i][j] = max(f[i][j], f[i-1][k] - E[i].p * k + E[i].p * j);
			}

			if(i==n) ans = max(ans, f[i][j]);
		}

		for(int j=1; j<=m; ++j) f[i][j] = max(f[i][j], f[i][j-1]);
	}

	printf("%d\n", ans);
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

