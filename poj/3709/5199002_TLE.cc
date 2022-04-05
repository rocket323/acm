#include <stdio.h>
#define MaxL 500010
#define ll long long
#define INF 1000000000000LL

ll n, k;  
ll a[MaxL], sum[MaxL], f[MaxL];
ll head, tail;
int Q[MaxL];

void init()
{
	scanf("%I64d%I64d", &n, &k);
	sum[0] = 0;
	for(ll i=1; i<=n; ++i)
	{
		scanf("%I64d", &a[i]);
		sum[i] = sum[i-1] + a[i];
	}
	//printf("%I64d\n", sum[n] - a[1] * n);
}

ll Min(ll a, ll b){ return (a<b)?a:b; }

void solve()
{

	f[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		f[i] = INF;
		for(int j=0; j<=i-k; ++j)
		{
			f[i] = Min(f[i], f[j] + sum[i] - sum[j] - (ll)a[j+1] * (i-j));
		}
	}

	printf("%I64d\n", f[n]);
}

int main()
{
	ll t;
	scanf("%I64d", &t);
	while(t--)
	{
		init();
		//for(int i=1; i<=n; ++i) printf("%I64d ", a[i]); puts("");
		solve();
	}
	return 0;
}
