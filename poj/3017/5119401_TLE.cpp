#include <stdio.h>
#define MaxL 100010
#define ll long long
#define INF 10000000000000LL

int n, a[MaxL];
long long m, s[MaxL], f[MaxL];

void init()
{
	s[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &a[i]);
		s[i] = (ll)s[i-1] + a[i];
	}
}

ll Min(ll a, ll b){ return (a<b)?a:b; }

int getMax(int s, int t)
{
	int ans = -1;
	for(int i=s; i<=t; ++i) if(ans < a[i]) ans = a[i];
	return ans;
}

void solve()
{
	f[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		f[i] = INF;
		for(int j=i-1; j>=0; --j)
		{
			if(s[i] - s[j] > m) break;
			f[i] = Min(f[i], f[j] + getMax(j+1, i));
		}
	}
	if(f[n]==INF) printf("-1\n");
	else printf("%I64d\n", f[n]);
}

int main()
{
	while(scanf("%d%I64d", &n, &m)!=EOF)
	{
		init();
		solve();
	}
	return 0;
}
