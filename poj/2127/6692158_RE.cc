#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 505

int n, m, a[maxl], b[maxl];
int f[maxl][maxl], mat[maxl], pa[maxl][maxl], pb[maxl][maxl];

void out(int na, int nb)
{
	if(pa[na][nb] == 0) printf("%d", a[na], b[nb]);
	else
	{
		out(pa[na][nb], pb[na][nb]);
		printf(" %d", a[na], b[nb]);
	}
}

void solve()
{
	memset(pa, -1, sizeof pa);
	memset(pb, -1, sizeof pb);
	memset(mat, -1, sizeof mat);

	f[0][0] = 0;
	mat[0] = 0;
	int ans = 0, ra = -1, rb = -1;
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j)
		{
			f[i][j] = 0;
			if(a[i] != b[j]) continue;

			for(int k=0; k<j; ++k)
			{
				if((k == 0 || b[k] < b[j]) && f[mat[k]][k] + 1 > f[i][j])
				{
					f[i][j] = f[mat[k]][k] + 1;
					pa[i][j] = mat[k];
					pb[i][j] = k;
				}
			}

			if(f[i][j] > ans)
			{
				ans = f[i][j];
				ra = i;
				rb = j;
			}
		}
		for(int j=1; j<=m; ++j) if(a[i] == b[j]) mat[j] = i;
	}

	printf("%d\n", ans);
	out(ra, rb);
	
}

int main()
{
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
	scanf("%d", &m);
	for(int i=1; i<=m; ++i) scanf("%d", &b[i]);

	solve();
	return 0;
}

