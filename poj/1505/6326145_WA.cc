#include <stdio.h>
#include <cstring>
#define maxl 520
#define ll long long
#define min(a,b) ((a<b)?a:b)

ll n, m, a[maxl], sum[maxl], f[maxl][maxl];
ll p[maxl][maxl];

ll max(ll a, ll b)
{
	return (a > b) ? a : b;
}

void out(ll pos, ll m)
{
	if(p[pos][m] == n)
	{
		for(ll i=pos; i<n-1; ++i) printf("%I64d ", a[i]);
		printf("%I64d\n", a[n-1]);
	}
	else
	{
		for(ll i=pos; i<p[pos][m]; ++i) printf("%I64d ", a[i]);
		printf("/ ");
		out(p[pos][m], m-1);
	}
}

void solve()
{
	scanf("%I64d%I64d", &n, &m);
	for(ll i=0; i<n; ++i) scanf("%I64d", &a[i]);

	sum[n] = 0;
	for(ll i=n-1; i>=0; --i) sum[i] = sum[i+1] + a[i];

	memset(f, 0x3f, sizeof f);
	f[n][0] = 0;

	for(ll i=n-1; i>=0; --i)
	{
		for(ll j=1; j<=m; ++j)
		{
			for(ll k=i+1; k<=n; ++k)
			{
				ll tmp = max(sum[i] - sum[k], f[k][j-1]);
				if(tmp < f[i][j])
				{
					f[i][j] = tmp;
					p[i][j] = k;
				}
			}
		}
	}
	out(0, m);
}

int main()
{
	ll t;
	scanf("%I64d", &t);
	while(t--)
	{
		solve();
	}
	return 0;
}

