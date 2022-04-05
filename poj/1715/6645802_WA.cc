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

void solve(int m, int n)
{
	if(m == 9) return;

	long long k;
	for(int i=15; i>=0; --i)
	{
		if(vis[i]) continue;
		if((k = A(16 - m, 8 - m)) < n) n -= k;
		else
		{
			vis[i] = 1;
			printf("%c", c[i]);
			break;
		}
	}
	solve(m + 1, n);
}

int main()
{
	fac[0] = 1;
	for(int i=1; i<=16; ++i) fac[i] = (ll)fac[i-1] * i;

	while(scanf("%I64d", &n) != EOF)
	{
		memset(vis, 0, sizeof vis);
		solve(1, n);
		puts("");
	}
	return 0;
}

