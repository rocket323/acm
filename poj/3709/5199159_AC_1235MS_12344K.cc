#include <stdio.h>
#define MaxL 500010
#define ll long long
#define INF 10000000000000LL

ll n, k;  
ll a[MaxL], sum[MaxL], f[MaxL];
ll head, tail;
int Q[MaxL];

void init()
{
	scanf("%lld%lld", &n, &k);
	sum[0] = 0;
	for(ll i=1; i<=n; ++i)
	{
		scanf("%lld", &a[i]);
		sum[i] = (ll)sum[i-1] + a[i];
	}
}

ll slope(int x, int y)
{
	ll up = (ll)f[x] - f[y] + sum[y] - sum[x] + (ll)a[x+1] * x - (ll)a[y+1] * y;
	ll dn = a[x+1] - a[y+1];
	//if(dn==0) return INF;
	//printf("%d %d %.3f\n", x, y, up * 1.0 / dn);
	return up;
}

void add_Q(ll now)
{
	while(tail-head>1)
	{
		ll a1 = slope(Q[tail-2], Q[tail-1]);
		ll a2 = slope(Q[tail-1], now);
		
		ll b1 = a[Q[tail-2]+1] - a[Q[tail-1]+1];
		ll b2 = a[Q[tail-1]+1] - a[now+1];
		
		if((ll)a1*b2 >= (ll)a2*b1) tail--;
		else break;
	}
	Q[tail++] = now;
}

void out()
{
	printf(" H : ");
	for(ll i=head; i<tail; ++i) printf("%d ", Q[i]);
	printf("\n");
}

void solve()
{


	f[0] = 0;
	for(ll i=1; i<k; ++i) f[i] = INF;
	f[k] = sum[k] - (ll)a[1] * k;
	
	head = tail = 0;
	Q[tail++] = 0;
	for(ll i=k+1; i<=n; ++i)
	{
		if(f[i-k]<INF) add_Q(i-k);
		
		while(tail-head>1 && slope(Q[head], Q[head+1]) >= (ll)i * (a[Q[head]+1] - a[Q[head+1]+1]) ) head++;
		
		if(head < tail)
		{
			int x = Q[head];
			f[i] = (ll)f[x] + sum[i] - sum[x] - (ll)a[x+1] * (i - x);
			
			
			//printf("%d %d %lld %lld\n", i, x, f[i], f[x]);
		}
		else f[i] = INF;
		
		
		
		//out();
	}
	printf("%lld\n", f[n]);
}

int main()
{
	ll t;
	scanf("%lld", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}
