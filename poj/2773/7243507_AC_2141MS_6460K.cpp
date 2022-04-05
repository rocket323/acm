#include <stdio.h>
#include <cstring>
#define maxl 1000010

int n, k, m;
int f[maxl], list[maxl], top;

void init()
{
	memset(f, -1, sizeof f);
	for(int i=2; i<maxl; ++i)
	{
		if(f[i] != -1) continue;
		f[i] = 1;
		for(int j=i+i; j<maxl; j+=i)
		{
			if(j % (i * i) == 0) f[j] = -2;
			if(f[j] == -1) f[j] = 1;
			else if(f[j] > 0) f[j]++;
		}
	}
	top = 0;
	for(int i=2; i<maxl; ++i)
	{
		if(f[i] != -2)
		{
			list[top++] = i;
		}
	}
}

int calc(int n)
{
	int ans = n;
	for(int i=0; i<top && list[i]<=m; ++i)
	{
		int num = list[i];
		if(m % num) continue;
		if(f[num] & 1) ans -= n / num;
		else ans += n / num;
	}
	return ans;
}

int main()
{
	init();
	while(scanf("%d%d", &m, &k) != EOF)
	{
		int l = 1, r = 1000000000, mid, ans = -1;
		while(l <= r)
		{
			mid = (l + r) >> 1;
			int x = calc(mid);
			if(x >= k)
			{
				ans = mid;
				r = mid - 1;
			}
			else l = mid + 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
