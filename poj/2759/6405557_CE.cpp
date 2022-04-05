#include <stdio.h>
#include <cstring>
#define maxl 10010
#define INF 100000000000LL
#define ll long long

ll n, m, a[2][maxl], s[3][maxl], sum;
ll f[maxl], g[maxl], p[3][maxl], low;

ll min(ll a, ll b){ return (a < b) ? a : b; }
ll max(ll a, ll b){ return (a > b) ? a : b; }

void init()
{
	//scanf("%I64d%I64d", &n, &m);
	low = -INF;
	sum = 0;
	for(ll i=0; i<2; ++i)
	{
		s[i][0] = 0;
		for(ll j=1; j<=n; ++j)
		{
			scanf("%I64d", &a[i][j]);
			sum += a[i][j];
			low = max(low, a[i][j]);
			s[i][j] = s[i][j-1] + a[i][j];
		}
	}
	for(ll i=0; i<=n; ++i) s[2][i] = s[0][i] + s[1][i];
}

bool check(ll lim)
{
	//printf("n %I64d\n", lim);
	ll flag = 0;
	if(lim == 8) flag = 1;
	for(ll i=0; i<3; ++i)
	{
		ll k = 0;
		p[i][0] = -1;
		for(ll j=1; j<=n; ++j)
		{
			while(s[i][j] - s[i][k] > lim) k++;
			p[i][j] = k;
//			if(flag) printf("%I64d ", p[i][j]);
		}
//		if(flag) printf("\n");
	}

	f[0] = g[0] = 0;
	for(ll i=1; i<=n; ++i)
	{
		/*
		f[i] = INF;

		ll j = p[2][i];

		if(j < i)
		{
			f[i] = min(f[i], f[j] + 1);
			f[i] = min(f[i], g[j] + 1);
			//if(flag && i == 2) printf("t %I64d %I64d %I64d\n", j, f[j] + 1, g[j] + 1);
		}
		*/
		ll j = p[2][i];

		if(j < i)
		{
			g[i] = min(g[i], g[j] + 1);
			//if(flag && i == 2) printf("t %I64d %I64d %I64d\n", j, f[j] + 1, g[j] + 1);
		}

		g[i] = INF;
		ll a = p[0][i], b = p[1][i], c = 2;
		while(a != b)
		{
			//if(flag) printf("g %I64d %I64d %I64d\n", i, a, b);
			g[i] = min(g[i], g[max(a, b)] + c);
			ll k = max(a, b);
			//if(s[2][i] - s[2][k] <= lim) g[i] = min(g[i], g[k] + 1);
			if(a > b) a = p[0][a];
			else b = p[1][b];
			c++;
		}
		g[i] = min(g[i], g[a] + c);
		//g[i] = min(g[i], f[a] + c);
		//if(flag) printf("p %I64d %I64d\n", i, g[i]);
	}
	//return min(f[n], g[n]) <= m;
	return g[n] <= m;
}

void solve()
{
	ll l = low, r = sum, mid, ans = -1;
	//printf("%I64d %I64d\n", l, r);
	while(l <= r)
	{
		ll mid = (l + r) / 2;
		if(check(mid))
		{
			r = mid - 1;
			ans = mid;
		}
		else l = mid + 1;
	}

	printf("%I64d\n", ans);
}

int main()
{
	//while(scanf("%I64d%I64d", &n, &m) != EOF)
	{
		scanf("%I64d%I64d", &n, &m);
		init();
		solve();
	}
	return 0;
}

