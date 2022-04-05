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

			int e;
			if(p[j] == 2) e = l[0] + l[1];
			else if(p[j] == 1) e = l[0];
			for(int k=i; k<=e; ++k)
			{
				int add = abs(v[k] - v[j]);
				int t1 = f[i][k] + f[k+1][j] + add;
				int t2 = f[i][k] + f[k][j-1] + add;
				int t3 = f[i][k] + f[k+1][j-1] + add;

				int t4 = f[i][k-1] + f[k+1][j] + add;
				int t5 = f[i][k-1] + f[k][j-1] + add;
				int t6 = f[i][k-1] + f[k+1][j-1] + add;

				int x1 = min(min(t1, t2), min(t3, t4));
				f[i][j] = min(min(f[i][j], x1), min(t5, t6));
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

