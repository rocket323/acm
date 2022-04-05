#include <stdio.h>
#define MaxL 500010
#define ll long long
#define INF 100000000000LL

int n, k;  
int a[MaxL];
ll sum[MaxL], f[MaxL];
int head, tail;
int Q[MaxL];

void init()
{
	scanf("%d%d", &n, &k);
	sum[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &a[i]);
		sum[i] = sum[i-1] + a[i];
	}
}

ll slope(int x, int y)
{
	return (ll)f[x] - f[y] + sum[y] - sum[x] + (ll)a[x+1] * x - (ll)a[y+1] * y;
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

void solve()
{
	f[0] = 0;
	head = tail = 0;

	for(int i=1; i<=n; ++i)
	{
		if(i-k>=0 && f[i-k]<INF) add_Q(i-k);
		
		while(tail-head>1 && slope(Q[head], Q[head+1]) >= (ll)i * (a[Q[head]+1] - a[Q[head+1]+1]) ) head++;
		
		if(head < tail)
		{
			int x = Q[head];
			f[i] = f[x] + sum[i] - sum[x] - (ll)a[x+1] * (i - x);
		}
		else f[i] = INF;
	}
	printf("%I64d\n", f[n]);
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}
