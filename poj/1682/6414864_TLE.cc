#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#define maxl 310
#define INF 0x3f3f3f3f
#define min(a,b) ((a<b)?a:b)

int n, l[3], b, c, v[maxl], p[maxl], f[maxl][maxl];

int val(int a, int b){ return (abs(v[a] - v[b])); }

void solve()
{
	n = 0;
	scanf("%d%d%d", &l[0], &l[1], &l[2]);
	for(int x=0; x<3; ++x)
	{
		for(int i=0; i<l[x]; ++i)
		{
			int val;
			scanf("%d", &val);
			v[++n] = val;
			p[n] = x;
		}
	}

	//for(int i=1; i<=n; ++i) printf("%d ", p[i]);
	//puts("");

	memset(f, 0x3f, sizeof f);
	for(int i=1; i<n; ++i) if(p[i] != p[i+1]) f[i][i+1] = val(i, i+1);
	for(int i=1; i<=n+1; ++i)for(int j=i-1; j>=0; --j) f[i][j] = 0;

	for(int len=3; len<=n; ++len)
	{
		for(int i=1, j=i+len-1; j<=n; ++i, ++j)
		{
			if(p[i] == p[j]) continue;

			int lsum = 0;
			for(int lt=i; lt<=j && p[lt]!=p[j]; ++lt)
			{
				int rsum = 0;
				lsum += abs(v[lt] - v[j]);
				for(int rt=j-1; rt>lt && p[rt]!=p[j]; --rt)
				{
					rsum += abs(v[rt] - v[j]);
					int t1 = f[lt][rt] + lsum + rsum;
					int t2 = f[lt][rt-1] + lsum + rsum;
					int t3 = f[lt+1][rt] + lsum + rsum;
					int t4 = f[lt+1][rt-1] + lsum + rsum;
					f[i][j] = min(f[i][j], min(min(t1, t2), min(t3, t4)));
				}
			}

			int rsum = 0;
			for(int rt=j-1; rt>=i && p[rt]!=p[j]; --rt)
			{
				rsum += abs(v[rt] - v[j]);
				int t1 = f[i][rt] + rsum;
				int t2 = f[i][rt-1] + rsum;
				f[i][j] = min(f[i][j], min(t1, t2));
			}

			lsum = 0;
			for(int lt=i; lt<=j && p[lt]!=p[j]; ++lt)
			{
				lsum += abs(v[lt] - v[j]);
				int t1 = f[lt][j-1] + lsum;
				int t2 = f[lt+1][j-1] + lsum;
				f[i][j] = min(f[i][j], min(t1, t2));
			}

			if(p[j] == 2 && p[i] == 0)
			{
				int s = l[0] + 1, e = l[0] + l[1], sum;
				for(int lt=s; lt<=e; ++lt)
				{
					sum = 0;
					for(int rt=lt; rt<=e; ++rt)
					{
						sum += abs(v[rt] - v[j]);
						f[i][j] = min(f[i][j], f[i][lt] + f[rt][j] + sum);
						f[i][j] = min(f[i][j], f[i][lt] + f[rt+1][j] + sum);
						f[i][j] = min(f[i][j], f[i][lt-1] + f[rt][j] + sum);
						f[i][j] = min(f[i][j], f[i][lt-1] + f[rt+1][j] + sum);
					}
				}
			}
		}
	}

	printf("%d\n", f[1][n]);
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		solve();
	}
	return 0;
}

