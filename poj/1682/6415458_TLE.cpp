#include <stdio.h>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#define maxl 310
#define INF 0x3f3f3f3f
#define min(a,b) ((a<b)?a:b)
using namespace std;

short n, l[3], b, c, v[maxl], p[maxl], f[maxl][maxl];

short val(short a, short b){ return (abs(v[a] - v[b])); }

void solve()
{
	n = 0;
	scanf("%d%d%d", &l[0], &l[1], &l[2]);
	for(short x=0; x<3; ++x)
	{
		for(short i=0; i<l[x]; ++i)
		{
			short val;
			//scanf("%ud", &val);
			cin >> val;
			//printf("n %d %d %d %d\n", x, l[x], i, val);
			v[++n] = val;
			p[n] = x;
		}
	}

	memset(f, 0x3f, sizeof f);
	for(short i=1; i<n; ++i) if(p[i] != p[i+1]) f[i][i+1] = val(i, i+1);
	for(short i=1; i<=n+1; ++i)for(short j=i-1; j>=0; --j) f[i][j] = 0;

	for(short len=3; len<=n; ++len)
	{
		for(short i=1, j=i+len-1; j<=n; ++i, ++j)
		{
			if(p[i] == p[j]) continue;

			short lsum = 0;
			for(short lt=i; lt<=j && p[lt]!=p[j]; ++lt)
			{
				short rsum = 0;
				lsum += abs(v[lt] - v[j]);
				for(short rt=j-1; rt>lt && p[rt]!=p[j]; --rt)
				{
					rsum += abs(v[rt] - v[j]);
					short t1 = f[lt][rt] + lsum + rsum;
					short t2 = f[lt][rt-1] + lsum + rsum;
					short t3 = f[lt+1][rt] + lsum + rsum;
					short t4 = f[lt+1][rt-1] + lsum + rsum;
					f[i][j] = min(f[i][j], min(min(t1, t2), min(t3, t4)));
				}
			}

			short rsum = 0;
			for(short rt=j-1; rt>=i && p[rt]!=p[j]; --rt)
			{
				rsum += abs(v[rt] - v[j]);
				short t1 = f[i][rt] + rsum;
				short t2 = f[i][rt-1] + rsum;
				f[i][j] = min(f[i][j], min(t1, t2));
			}

			lsum = 0;
			for(short lt=i; lt<=j && p[lt]!=p[j]; ++lt)
			{
				lsum += abs(v[lt] - v[j]);
				short t1 = f[lt][j-1] + lsum;
				short t2 = f[lt+1][j-1] + lsum;
				f[i][j] = min(f[i][j], min(t1, t2));
			}

			if(p[j] == 2 && p[i] == 0)
			{
				short s = l[0] + 1, e = l[0] + l[1], sum;
				for(short lt=s; lt<=e; ++lt)
				{
					sum = 0;
					for(short rt=lt; rt<=e; ++rt)
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
	short t;
	scanf("%d", &t);
	while(t--)
	{
		solve();
	}
	return 0;
}

