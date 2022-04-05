#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 1000010
#define INF 0x3f3f3f3f

int f[2], t[2], n, d[2][maxl], a[maxl], d1, d2, p1, p2, s[2][maxl];

int main()
{
	while(scanf("%d", &n), n)
	{

		scanf("%d%d%d%d", &d1, &p1, &d2, &p2);

		s[0][0] = s[1][0] = 0;
		for(int i=1; i<=n; ++i)
		{
			scanf("%d", &d[0][i]);
			s[0][i] = s[0][i-1] + d[0][i];
		}
		for(int i=0; i<=n; ++i) scanf("%d", &a[i]);
		for(int i=1; i<=n; ++i)
		{
			scanf("%d", &d[1][i]);
			s[1][i] = s[1][i-1] + d[1][i];
		}

		if(p1 > p2)
		{
			swap(d1, d2);
			swap(p1, p2);
		}

		int x1 = INF, x2 = INF;

		for(int i=0; i<=p1; ++i) x1 = min(x1, s[0][p1] - s[0][i] + s[1][p1] - s[1][i] + a[i]);
		for(int i=p2; i<=n; ++i) x2 = min(x2, s[0][i] - s[0][p2] + s[1][i] - s[1][p2] + a[i]);

		if(d1 == 0) f[0] = 0, f[1] = x1;
		else f[0] = x1, f[1] = 0;

		for(int i=p1+1; i<=p2; ++i)
		{
			t[0] = min(f[0] + d[0][i], f[1] + d[1][i] + a[i]);
			t[1] = min(f[1] + d[1][i], f[0] + d[0][i] + a[i]);

			f[0] = t[0], f[1] = t[1];

		}

		int ans = min(f[d2], f[d2^1] + x2);
		printf("%d\n", ans);
	}
	return 0;
}

