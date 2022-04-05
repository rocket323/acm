#include <stdio.h>
#include <algorithm>
using namespace std;
#define maxl 40010
#define INF 0x3f3f3f3f

int n, a[maxl], f[maxl], Q[maxl], top;

bool cmp(int x, int y)
{
	return a[x] < a[y];
}

void solve()
{
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) scanf("%d", &a[i]);

	top = 0;
	a[0] = -INF;
	Q[top++] = 0;
	f[0] = 0;

	for(int i=1; i<=n; ++i)
	{
		int idx = (int)(lower_bound(Q, Q+top, i, cmp) - Q);
		f[i] = f[Q[idx-1]] + 1;
		Q[idx] = i;
		if(idx == top) top++;
	}
	printf("%d\n", f[Q[top-1]]);
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--) solve();
	return 0;
}

