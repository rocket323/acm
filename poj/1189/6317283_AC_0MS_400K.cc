#include <stdio.h>
#include <cstring>
#define ll long long

int n, m;
char str[100][100][2];
ll f[52][52];

void init()
{
	for(int i=0; i<=n; ++i)
	{
		for(int j=0; j<=i; ++j) scanf("%s", str[i][j]);
	}
}

ll gcd(ll a, ll b)
{
	if(!b) return a;
	else return gcd(b, a%b);
}

void solve()
{
	memset(f, 0, sizeof f);
	ll sum = (1LL << (n));
	f[0][0] = sum;

	for(int i=0; i<=n; ++i)
	{
		for(int j=0; j<=i; ++j)
		{
			if(str[i][j][0] == '.') f[i+2][j+1] += f[i][j];
			else
			{
				f[i+1][j] += f[i][j] / 2;
				f[i+1][j+1] += f[i][j] / 2;
			}
		}
	}

	if(f[n][m] == 0) puts("0/1");
	else
	{
		ll d = gcd(f[n][m], sum);
		printf("%I64d/%I64d\n", f[n][m] / d, sum / d);
	}
}

int main()
{
	while(scanf("%d%d", &n, &m) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

