#include <stdio.h>
#include <cstring>

int n, a[30], f[9000][30], s;

int dp(int s, int p)
{
	if(f[s][p] != -1) return f[s][p];

	if(s == 1) return f[s][p] = 0;

	for(int i=1; i<a[p] && i<s; ++i)
	{
		if(!dp(s - i, (p + 1) % (2*n))) return f[s][p] = 1;
	}
	return f[s][p] = 0;
}

int main()
{
	while(scanf("%d", &n), n)
	{
		scanf("%d", &s);
		for(int i=0; i<2*n; ++i) scanf("%d", &a[i]);

		memset(f, -1, sizeof f);
		if(dp(s, 0)) puts("1");
		else puts("0");
	}
	return 0;
}

