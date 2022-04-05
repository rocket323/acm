#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define ll long long
#define maxl 50010

ll c[5][maxl], a[maxl], b[maxl], n;

ll lowbit(ll n)
{
	return n & -n;
}

ll get_sum(ll key, ll n)
{
	n++;
	ll ans = 0;
	while(n)
	{
		ans += c[key][n];
		n -= lowbit(n);
	}
	return ans;
}

void add(ll key, ll n, ll num)
{
	n++;
	while(n < maxl)
	{
		c[key][n] += num;
		n += lowbit(n);
	}
}

int main()
{
	while(scanf("%I64d", &n) != EOF)
	{
		for(ll i=1; i<=n; ++i)
		{
			scanf("%I64d", &a[i]);
			b[i] = a[i];
		}

		sort(b + 1, b + 1 + n);
		ll sz = unique(b + 1, b + 1 + n) - b - 1;

		memset(c, 0, sizeof c);
		add(0, 0, 1);

		ll ans = 0;
		for(ll j=1; j<=n; ++j)
		{
			for(ll i=1; i<=5; ++i)
			{
				ll idx = lower_bound(b + 1, b + 1 + sz, a[j]) - b;
				ll f = get_sum(i - 1, idx - 1);
				if(i == 5) ans += f;
				add(i, idx, f);
			}
		}
		printf("%I64d\n", ans);
	}
	return 0;
}

