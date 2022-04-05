#include <stdio.h>
#include <cstring>
#define MaxL 1000010

int f[MaxL];

void cal_euler()
{
	memset(f, -1, sizeof f);
	for(int i=2; i<MaxL; ++i)
	{
		if(f[i] != -1) continue;
		f[i] = i - 1;
		int j = i + i;
		while(j < MaxL)
		{
			if(f[j] == -1) f[j] = j;
			f[j] = f[j] / i * (i - 1);
			j += i;
		}
	}
}

long long solve(int n)
{
	long long ans = 0;
	for(int i=2; i<=n; ++i) ans += f[i];
	return ans;
}

int main()
{
	int n;
	cal_euler();
	while(scanf("%d", &n) && n)
	{
		printf("%I64d\n", solve(n));
	}
	return 0;
}