#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 10100

struct node
{
	int p, d;
}
A[maxl];

int n, f[maxl];

bool cmp(node A, node B)
{
	return A.d < B.d;
}

int max(int a, int b)
{
	return (a>b)?a:b;
}

void solve()
{
	for(int i=1; i<=n; ++i) scanf("%d%d", &A[i].p, &A[i].d);

	sort(A+1, A+n+1, cmp);

	memset(f, 0, sizeof f);

	int ans = 0;
	for(int i=1; i<=n; ++i)
	{
		for(int j=A[i].d; j>0; --j)
		{
			f[j] = max(f[j], f[j-1] + A[i].p);
			ans = max(ans, f[j]);
		}
	}

	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		solve();
	}
	return 0;
}

