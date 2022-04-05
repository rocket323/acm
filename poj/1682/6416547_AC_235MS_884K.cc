#include <stdio.h>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#define maxl 310
#define min(a,b) ((a<b)?a:b)
using namespace std;

short n, l[3], b, c, v[maxl], p[maxl], f[maxl][maxl], val;

void solve()
{
	n = 0;
	scanf("%d%d%d", &l[0], &l[1], &l[2]);
	for(short x=0; x<3; ++x)
	{
		for(short i=0; i<l[x]; ++i)
		{
			cin >> val;
			v[++n] = val;
			p[n] = x;
		}
	}

	memset(f, 0x1f, sizeof f);
	for(short i=1; i<n; ++i) if(p[i] != p[i+1]) f[i][i+1] = abs(v[i] - v[i+1]);
	for(short i=1; i<=n+1; ++i)for(short j=i-1; j>=0; --j) f[i][j] = 0;

	for(short len=3; len<=n; ++len)
	{
		for(short i=1, j=i+len-1; j<=n; ++i, ++j)
		{
			if(p[i] == p[j]) continue;

			short e;
			if(p[j] == 2) e = l[0] + l[1];
			else if(p[j] == 1) e = l[0];
			for(short k=i; k<=e; ++k)
			{
				short add = abs(v[k] - v[j]);
				short t1 = f[i][k] + f[k+1][j] + add;
				short t2 = f[i][k] + f[k][j-1] + add;
				short t3 = f[i][k] + f[k+1][j-1] + add;

				short t4 = f[i][k-1] + f[k+1][j] + add;
				short t5 = f[i][k-1] + f[k][j-1] + add;
				short t6 = f[i][k-1] + f[k+1][j-1] + add;

				short x1 = min(min(t1, t2), min(t3, t4));
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

