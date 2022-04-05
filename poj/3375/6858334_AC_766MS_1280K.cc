#include <stdio.h>
#include <cstring>
#include <algorithm>
#define maxl 2010
#define ADD 2010
#define INF 1000000000000LL
#define ll long long
#define abs(n) ((n) > 0 ? (n) : -(n))
using namespace std;

ll a[100010], b[maxl], n, m;
ll f[2][3 * maxl], mat[maxl];

void init()
{
	for(ll i=1; i<=m; ++i) scanf("%lld", &a[i]);
	for(ll i=1; i<=n; ++i) scanf("%lld", &b[i]);

	sort(a + 1, a + 1 + m);
	sort(b + 1, b + 1 + n);
}

void solve()
{
	memset(f, 0x3f, sizeof f);

	ll now = 1;
	for(ll i=1; i<=n; ++i)
	{
		while(now < m && abs(a[now+1] - b[i]) <= abs(a[now] - b[i])) now++;
		mat[i] = now;
	}

	/*
	for(ll i=-n; i<=n; ++i)
	{
		ll k = mat[1] + i;
		if(k < 1 || k > m) continue;

		f[0][i + ADD] = abs(a[k] - b[1]);
		f[0][i + ADD] = min(f[0][i + ADD], f[0][i + ADD - 1]);
	}
	*/

	ll idx = 0, ans = INF;

	memset(f[0], 0, sizeof f[0]);

	/*
	for(int i=1; i<=m; ++i) printf("%lld ", a[i]);
	puts("");
	for(int i=1; i<=n; ++i) printf("%lld ", b[i]);
	puts("");
	*/

	//for(ll i=1; i<=n; ++i) printf("%lld : %lld ", mat[i], abs(b[i] - a[mat[i]]));
	//puts("");

	for(ll i=1; i<=n; ++i)
	{
		idx ^= 1;
		memset(f[idx], 0x3f, sizeof f[idx]);
		for(ll j=-n; j<=n; ++j)
		{
			ll k = mat[i] + j;
			if(k < 1 || k > m) continue;

			ll pre = k - 1 - mat[i-1];
			//if(pre < -n || pre > n) continue;
			//if(pre + ADD < 0 || pre + ADD > n + n + ADD) continue;
			if(pre > n) pre = n;
			f[idx][j + ADD] = min(f[idx][j + ADD - 1], f[idx^1][pre + ADD] + abs(a[k] - b[i]));

			//if(i == 1) puts("here");

			//printf("%lld %lld %lld\n", i, k, f[idx][j + ADD]);

			if(i == n) ans = min(ans, f[idx][j + ADD]);
		}
		//for(int j=1; j<=n+n+ADD; ++j) f[idx][j] = min(f[idx][j], f[idx][j-1]);
	}
	printf("%lld\n", ans);
}

int main()
{
	while(scanf("%lld%lld", &m, &n) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

