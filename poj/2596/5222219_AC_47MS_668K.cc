#include <stdio.h>
#include <cstring>
#define Max(a,b) ((a>b)?a:b)

int f[1<<10][10][6], n, A[10][6];
int opp[6] = {5, 3, 4, 1, 2, 0};
int tot;

void init()
{
	scanf("%d", &n);
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<6; ++j) scanf("%d", &A[i][j]);
	}
}

int slectMax(int j, int k)
{
	int ans = -1;
	for(int i=0; i<6; ++i)
	{
		if(i==k || i==opp[k]) continue;
		ans = Max(ans, A[j][i]);
	}
	return ans;
}

void solve()
{
	int ans = 0;
	tot = (1<<n);
	memset(f, -1, sizeof f);
	f[0][0][0] = 0;
	for(int i=0; i<tot; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			if(i && !(i&(1<<j))) continue;
			for(int k=0; k<6; ++k)
			{
				if(f[i][j][k]==-1) continue;
				for(int jj=0; jj<n; ++jj)
				{
					if(i&(1<<jj)) continue;
					for(int kk=0; kk<6; ++kk)
					{
						if(i==0 || A[jj][opp[kk]]==A[j][k])
						{
							int x = slectMax(jj, kk);
							f[i|(1<<jj)][jj][kk] = Max(f[i|(1<<jj)][jj][kk], f[i][j][k] + x);
						}
					}
				}
				if((i==tot-1) && f[i][j][k] > ans) ans = f[i][j][k];
			}
		}
	}
	printf("%d\n", ans);
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}
