#include <stdio.h>
#include <cstring>
#include <math.h>
#define INF 1000000000000LL
#define ll long long

ll d, n;

void solve()
{
	ll k = ceil(sqrt(d));

	ll ans = 0;
	if(n <= k)
	{
		for(int i=1; i<=n; ++i)
		{
			ans += ceil(d * 1.0 / i);
		}
		printf("%I64d\n", ans);
	}
	else
	{
		for(int i=1; i<=k; ++i) ans += ceil(d * 1.0 / i);

		//printf("%lld\n", k + 1);

		int down = ceil(d * 1.0 / n);
		int up = ceil(d * 1.0 / (k + 1));

		for(int x = down; x <= up; ++x)
		{

			ll l = INF , r = -INF;
			if(x - 1 == 0) r = n;
			else if(d % (x - 1) == 0) r = d / (x - 1) - 1;

			l = ceil(d * 1.0 / x);


			if(l <= k + 1) l = k + 1;
			if(r > n) r = n;
			//printf("%d %lld %lld\n", x, l, r);

			if(l <= r) ans += (ll)x * (r - l + 1);
		}
		printf("%I64d\n", ans);
	}
}

int main()
{
	while(scanf("%I64d%I64d", &d, &n), (d + n))
	{
		solve();
	}
	return 0;
}

