#include <stdio.h>
#include <cstring>
#define mod 9973
#define ll long long

int n, m, q, a[10][10], x, y, B[10][10], T[10][10], cnt;

void init()
{
	scanf("%d%d%d", &n, &m, &q);
	for(int i=0; i<m; ++i) for(int j=0; j<m; ++j) a[i][j] = 1;
	for(int i=0; i<q; ++i)
	{
		scanf("%d%d", &x, &y);
		a[x-1][y-1] = a[y-1][x-1] = 0;
	}
	cnt = 0;
	for(int i=0; i<m; ++i) if(a[i][i]) cnt++;
}

int phi(int n)
{
	int ans = n;
	for(int i=2; (ll)i*i<=n; ++i)
	{
		if(n % i == 0)
		{
			ans = ans / i * (i - 1);
			while(n % i == 0) n /= i;
		}
	}
	if(n > 1) ans = ans / n * (n - 1);
	return ans % mod;
}

void extend_gcd(ll a, ll b, ll& d, ll& x, ll& y)
{
	if(b == 0){ d = a; x = 1; y = 0; }
	else
	{
		extend_gcd(b, a % b, d, y, x);
		y -= a / b * x;
	}
}

void matrix(int C[][10], int A[][10], int B[][10])
{
	for(int i=0; i<m; ++i)
	{
		for(int j=0; j<m; ++j)
		{
			C[i][j] = 0;
			for(int k=0; k<m; ++k)
			{
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
			}
		}
	}
}

int calc(int n)
{
	if(n == 0) return cnt;
	memset(B, 0, sizeof B);
	for(int i=0; i<m; ++i) B[i][i] = 1;
	memcpy(T, a, sizeof a);

	int tmp[10][10];
	while(n)
	{
		if(n & 1)
		{
			matrix(tmp, B, T);
			memcpy(B, tmp, sizeof tmp);
		}
		matrix(tmp, T, T);
		memcpy(T, tmp, sizeof tmp);
		n >>= 1;
	}

	int ans = 0;
	for(int i=0; i<m; ++i)
	{
		for(int j=0; j<m; ++j)
		{
			if(!a[i][j]) continue;
			ans = (ans + B[i][j]) % mod;
		}
	}
	return ans;
}

void solve()
{
	int ans = 0;

	//for(int i=1; i<=3; ++i) printf("%d %d\n", i, calc(i-1));

	for(int i=1; (long long)i * i<=n; ++i)
	{
		if(n % i) continue;
		ans = (ans + phi(n / i) * calc(i-1)) % mod;
		ll k = n / i;
		if(k == i) continue;
		ans = (ans + phi(n / k) * calc(k-1)) % mod;
	}

	ll d, x, y;
	extend_gcd(n, mod, d, x, y);
	x = (x % mod + mod) % mod;

	ans = ((ll)ans * x) % mod;
	printf("%d\n", ans);
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

