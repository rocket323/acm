#include <stdio.h>
#include <cstring>
#define MaxL 10010

int n, a[MaxL], s[MaxL], p;
int pos[MaxL];

void init()
{
	s[0] = 0;
	p = -1;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &a[i]);
		s[i] = (s[i-1] + a[i]) % n;
		if(s[i]==0) p = i;
	}
}

void solve()
{
	if(p != -1)
	{
		printf("%d\n", p);
		for(int i=1; i<=p; ++i) printf("%d\n", a[i]);
		return;
	}
	memset(pos, -1, sizeof pos);
	pos[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		if(pos[s[i]] != -1)
		{
			printf("%d\n", i - pos[s[i]]);
			for(int j=pos[s[i]]+1; j<=i; ++j) printf("%d\n", a[j]);
			return;
		}
	}
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		init();
		solve();
	}
	return 0;
}