#include <stdio.h>
#include <cstring>

char str[20];

int C(int n, int m)
{
	if(n < m) return 0;
	int ans = 1;
	for(int i=0; i<m; ++i) ans *= (n - i);
	for(int i=1; i<=m; ++i) ans /= i;
	return ans;
}

int solve(int now, int len)
{
	if(now == len) return 0;
	else
	{
		int ans = solve(now + 1, len);
		char st = 'a';
		if(now > 0) st = str[now - 1] + 1;
		for(char ch=st; ch<str[now]; ch++) ans += C('z' - ch, len - now - 1);
		return ans;
	}
}

bool check(char str[])
{
	for(int i=1; str[i]; ++i)
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
			int ans = 0;
			for(int i=1; i<strlen(str); ++i) ans += C(26, i);
			printf("%d\n", solve(0, strlen(str)) + ans + 1);
		}
	}

	return 0;
}

