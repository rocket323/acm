#include <stdio.h>
#include <cstring>
#define ll long long

ll n;
int vis[20];
ll fac[27];
char c[] = "0123456789ABCDEF";

ll A(ll n, ll m)
{
	return fac[n] / fac[n - m];
}

void solve(int m, int n, int len)
{
	if(m == len + 1) return;

	long long k;
	for(int i=15; i>=0; --i)
	{
		if(vis[i]) continue;
		if((k = A(16 - m, len - m)) < n) n -= k;
		else
		{
			vis[i] = 1;
			printf("%c", c[i]);
			break;
		}
	}
	solve(m + 1, n, len);
}

int main()
{
	fac[0] = 1;
	for(int i=1; i<=16; ++i) fac[i] = (ll)fac[i-1] * i;

	while(scanf("%I64d", &n) != EOF)
	{
		memset(vis, 0, sizeof vis);

		int len = -1;
		ll k;
		for(int i=8; i>=1; --i)
		{
			k = 15LL * A(15, i - 1);
			if(k < n) n -= k;
			else
			{
				len = i;
				break;
			}
		}

		solve(1, n, len);
		puts("");
	}
	return 0;
}

