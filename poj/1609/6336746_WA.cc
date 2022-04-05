#include <stdio.h>
#include <cstring>
#include <algorithm>
#define maxl 10100
using namespace std;

struct node
{
	int a, b;
}
A[maxl];

int f[maxl][110], n, ans;

int max(int a, int b){ return (a > b) ? a : b; }

bool cmp(node A, node B)
{
	return (A.a < B.a);
}

void init()
{
	for(int i=1; i<=n; ++i) scanf("%d%d", &A[i].a, &A[i].b);
	sort(A+1, A+1+n, cmp);
}

void solve()
{
	memset(f, 0x80, sizeof f);
	f[0][0] = 0;
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<=100; ++j)
		{
			if(f[i][j] < 0) continue;
			f[i+1][j] = max(f[i+1][j], f[i][j]);
			if(A[i+1].b >= A[i].b) f[i+1][A[i+1].b] = max(f[i+1][A[i+1].b], f[i][j] + 1);
		}
	}
	for(int i=1; i<=100; ++i) ans = max(ans, f[n][i]);
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d", &n), n)
	{
		init();
		solve();
	}
	puts("*");
	return 0;
}

