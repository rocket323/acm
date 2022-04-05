#include <stdio.h>
#include <cstring>
#define ll long long

char str[20];

ll C(ll n, ll m)
{
	if(n < m) return 0;
	ll ans = 1;
	for(ll i=0; i<m; ++i) ans *= (n - i);
	for(ll i=1; i<=m; ++i) ans /= i;
	return ans;
}

ll solve(ll now, ll len)
{
	if(now == len) return 0;
	else
	{
		ll ans = solve(now + 1, len);
		char st = 'a';
		if(now > 0) st = str[now - 1] + 1;
		for(char ch=st; ch<str[now]; ch++) ans += C('z' - ch, len - now - 1);
		return ans;
	}
}

bool check(char str[])
{
	for(ll i=1; str[i]; ++i)
	{
		if(str[i] <= str[i-1]) return 0;
	}
	return 1;
}

int main()
{
	while(scanf("%s", str) != EOF)
	{
		if(!check(str)) puts("0");
		else
		{
			ll ans = 0;
			for(ll i=1; i<strlen(str); ++i) ans += C(26, i);
			printf("%I64d\n", solve(0, strlen(str)) + ans + 1);
		}
	}

	return 0;
}

