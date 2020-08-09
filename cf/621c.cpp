#include <stdio.h>
#include <cstring>
#define maxl 100010
#define ll long long

int n, p, l[maxl], r[maxl], len[maxl], cnt[maxl];
double f0[maxl], f1[maxl], g0[maxl], g1[maxl];

int main()
{
	while(scanf("%d%d", &n, &p) != EOF)
	{
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d", &l[i], &r[i]);
			len[i] = r[i] - l[i] + 1;
			cnt[i] = r[i] / p - (l[i] + p - 1) / p + 1;
		}

		double ans = 0;
		for(int i = 0; i < n; ++i)
		{
			int j = (i + 1) % n;
			double p1 = 1.0 - cnt[i] * 1.0 / len[i];
			double p2 = 1.0 - cnt[j] * 1.0 / len[j];
			double f = 1 - p1 * p2;
			ans += f * 2000;
		}
		printf("%.8lf\n", ans);
	}

	return 0;
}

