#include <stdio.h>
#include <cstring>
#define MaxL 2000010
#define ADD 1000
#define max(a,b) ((a>b)?a:b)

int f[2][MaxL], n, a[101], b[101];
int pos[101], neg[101];

void solve()
{
	memset(f, 0x80, sizeof f);

	f[0][0 + ADD] = 0;
	int idx = 0;
	for(int i=0; i<n; ++i)
	{
		memset(f[idx^1], 0x80, sizeof f[idx^1]);

		for(int j=neg[i]; j<=pos[i]; ++j)
		{
			f[idx^1][j+ADD] = max(f[idx^1][j+ADD], f[idx][j+ADD]);
			f[idx^1][j+a[i]+ADD] = max(f[idx^1][j+a[i]+ADD], f[idx][j+ADD] + b[i]);
		}
		idx ^= 1;
	}

	int ans = 0;
	for(int i=0; i<=pos[n]; ++i)
	{
		if(f[idx][i+ADD]>=0 && f[idx][i+ADD]+i>ans) ans = f[idx][i+ADD] + i;
	}
	printf("%d\n", ans);
}

int main()
{
	scanf("%d", &n);
	pos[0] = neg[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d%d", &a[i], &b[i]);
		if(a[i]>=0) pos[i] = pos[i-1] + a[i], neg[i] = neg[i-1];
		else pos[i] = pos[i-1], neg[i] = neg[i-1] + a[i];
	}
	solve();
	return 0;
}
