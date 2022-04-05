#include <stdio.h>
#include <cstring>

int a[101], l[101];
int f[100010], n, m;
char S[11][11];

int getID(char t[])
{
	for(int i=0; i<m; ++i)
		if(strcmp(S[i], t)==0) return i;
	return -1;
}

void init()
{
	for(int i=0; i<m; ++i) scanf("%s", S[i]);

	char t[10];
	for(int i=1; i<=n; ++i)
	{
		scanf("%d%s", &a[i], t);
		l[i] = getID(t);
	}
}

int go(int idx)
{
	int sum = 0;

	for(int i=1; i<=n; ++i)
		if(l[i]==idx) sum += a[i];

	memset(f, 0, sizeof f);
	f[0] = 1;

	for(int i=1; i<=n; ++i)
	{
		if(l[i]!=idx) continue;

		for(int j=sum; j>=a[i]; --j)
			if(f[j-a[i]]) f[j] = 1;
	}

	for(int i=(sum+1)/2; i<=sum; ++i)
		if(f[i]) return i;
}

void solve()
{
	int ans = 0;
	for(int i=0; i<m; ++i) ans += go(i);
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d", &m, &n) && (n+m))
	{
		init();
		solve();
	}
	return 0;
}
