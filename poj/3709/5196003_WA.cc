#include <stdio.h>
#define MaxL 500010
#define ll long long
#define INF 1000000000LL

ll n, k;  
ll a[MaxL], sum[MaxL], f[MaxL];
ll head, tail;
ll Q[MaxL];

void init()
{
	scanf("%I64d%I64d", &n, &k);
	sum[0] = 0;
	for(ll i=1; i<=n; ++i)
	{
		scanf("%I64d", &a[i]);
		sum[i] = sum[i-1] + a[i];
	}
}

double slope(ll x, ll y)
{
	ll up = f[x] - f[y] + sum[y] - sum[x] + (ll)a[x+1] * x - (ll)a[y+1] * y;
	ll dn = a[x+1] - a[y+1];
	if(dn==0) return 1000000;
	//printf("%I64d %I64d %.3f\n", x, y, up * 1.0 / dn);
	return up * 1.0 / dn;
}

void add_Q(ll now)
{
	while(tail-head>1)
	{
		double k1 = slope(Q[tail-2], Q[tail-1]);
		double k2 = slope(Q[tail-1], now);
		if(k1 >= k2) tail--;
		else break;
	}
	Q[tail++] = now;
}

void out()
{
	printf(" H : ");
	for(ll i=head; i<tail; ++i) printf("%I64d ", Q[i]);
	printf("\n");
}

void solve()
{

	//for(ll i=1; i<=n; ++i) printf("%I64d ", a[i]);
	//printf("\n\n");

	f[0] = 0;
	for(ll i=1; i<k; ++i) f[i] = INF;
	f[k] = sum[k] - (ll)a[1] * k;
	
	//printf("%I64d\n", f[k]);
	
	head = tail = 0;
	Q[tail++] = 0;
	for(ll i=k+1; i<=n; ++i)
	{
		if(f[i-k]<INF) add_Q(i-k);
		
		while(tail-head>1 && slope(Q[head], Q[head+1])<=i) head++;
		
		if(head < tail)
		{
			ll x = Q[head];
			f[i] = f[x] + sum[i] - sum[x] - (ll)a[x+1] * (i - x);
		}
		else f[i] = INF;
		
		//printf("%I64d %I64d %I64d %I64d\n", i, x, f[i], f[x]);
		
		//out();
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
		solve();
	}
	return 0;
}
