#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 50010

int c[5][maxl], a[maxl], b[maxl], n;

int lowbit(int n)
{
	return n & -n;
}

int get_sum(int key, int n)
{
	n++;
	int ans = 0;
	while(n)
	{
		ans += c[key][n];
		n -= lowbit(n);
	}
	return ans;
}

void add(int key, int n, int num)
{
	n++;
	while(n < maxl)
	{
		c[key][n] += num;
		n += lowbit(n);
	}
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		for(int i=1; i<=n; ++i)
		{
			scanf("%d", &a[i]);
			b[i] = a[i];
		}

		sort(b + 1, b + 1 + n);
		int sz = unique(b + 1, b + 1 + n) - b - 1;

		memset(c, 0, sizeof c);
		add(0, 0, 1);

		int ans = 0;
		for(int j=1; j<=n; ++j)
		{
			for(int i=1; i<=5; ++i)
			{
				int idx = lower_bound(b + 1, b + 1 + sz, a[j]) - b;
				int f = get_sum(i - 1, idx - 1);
				if(i == 5) ans += f;
				add(i, idx, f);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

