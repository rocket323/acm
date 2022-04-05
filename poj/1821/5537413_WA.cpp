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
	scanf("%d%d", &m, &n);
	for(int i=1; i<=n; ++i) scanf("%d%d%d", &E[i].l, &E[i].p, &E[i].s);
	sort(E+1, E+1+n, cmp);
}

void go()
{
	memset(f, 0x80, sizeof f);
	for(int i=0; i<E[1].s; ++i) f[0][i] = 0;

	int ans = -INF;


	for(int i=1; i<=n; ++i)
	{
		for(int j=E[i].s; j<=E[i].s+E[i].l-1 && j<=m; ++j)
		{
			if(i<n) f[i][j] = f[i-1][j];

			for(int p=E[i].s; p>=0 && p>=j-E[i].l; p--)
			{
				f[i][j] = max(f[i][j], f[i-1][p] + (j-p) * E[i].p);
			}

			if(i==n) ans = max(ans, f[i][j]);
		}
	}
	printf("%d\n", ans);
}

int fun(int i, int idx)
{
	return f[i-1][idx] - E[i].p * idx;
}

void solve()
{
	memset(f, 0x80, sizeof f);
	for(int i=0; i<E[1].s; ++i) f[0][i] = 0;

	int ans = -INF, idx;

	for(int i=1; i<=n; ++i)
	{
		head = tail = idx = 0;
		for(int j=E[i].s; j<=E[i].s+E[i].l-1 && j<=m; ++j)
		{
			if(i<n) f[i][j] = f[i-1][j];

			while(idx<=j)
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
	}

	printf("%d\n", ans);
}

int main()
{
	init();
	go();
	//solve();
	return 0;
}

