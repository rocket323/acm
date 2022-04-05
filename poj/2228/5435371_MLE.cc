#include <stdio.h>
#include <cstring>
#define MaxL 3831
#define max(a,b) ((a>b)?a:b)

int n, b;
int f[MaxL][MaxL][2], u[MaxL];

int dp(int idx, int nap, int flag)
{
	if(nap <= 1) return 0;
	if(f[idx][nap][flag] != -1) return f[idx][nap][flag];

	f[idx][nap][flag] = 0;
	int pre = (idx + n - 1) % n;

	if(flag==1)
	{
		f[idx][nap][1] = max(f[idx][nap][1], dp(pre, nap-1, 0));
		f[idx][nap][1] = max(f[idx][nap][1], dp(pre, nap-1, 1) + u[idx]);
	}
	else
	{
		f[idx][nap][0] = max(f[idx][nap][0], dp(pre, nap, 0));
		f[idx][nap][0] = max(f[idx][nap][0], dp(pre, nap, 1));
	}
	return f[idx][nap][flag];
}

void solve()
{
	memset(f, -1, sizeof f);

	int ans = 0;
	for(int i=0; i<n; ++i)
	{
		ans = max(ans, max(dp(i, b, 0), dp(i, b, 1)));
		//printf("%d %d %d\n", i, dp(i, b, 0), dp(i, b, 1));
	}
	printf("%d\n", ans);
}

int main()
{
	scanf("%d%d", &n, &b);
	for(int i=0; i<n; ++i) scanf("%d", &u[i]);
	solve();
	return 0;
}

