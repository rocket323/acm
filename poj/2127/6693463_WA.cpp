#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;
#define maxl 505

short n, m, f[maxl][maxl], a[maxl], b[maxl], mat[maxl], pa[maxl][maxl], pb[maxl][maxl];

void out(short na, short nb)
{
	if(pa[na][nb] == 0) cout << a[na]; 
	else
	{
		out(pa[na][nb], pb[na][nb]);
		cout << ' ' << a[na];	
	}
}

void solve()
{
	short ans = 0, ra = -1, rb = -1;
	for(int i=0; i<=n; ++i) for(int j=0; j<=m; ++j) f[i][j] = 0;

	mat[0] = 0;
	for(short i=1; i<=n; ++i)
	{
		short k = 0;
		for(short j=1; j<=m; ++j)
		{
			f[i][j] = f[i-1][j];
			if(a[i] > b[j] && f[i][k] < f[i][j]) k = j;
			if(a[i] == b[j] && f[i][k] + 1 > f[i][j])
			{
				f[i][j] = f[i][k] + 1;
				pa[i][j] = mat[k];
				pb[i][j] = k;
				mat[j] = i;
			}

			if(f[i][j] > ans)
			{
				ra = i;
				rb = j;
				ans = f[i][j];
			}
		}
	}

	cout << ans << endl;
	if(ans)
	{
		out(ra, rb);
		cout << endl;
	}
}

int main()
{
	cin >> n;
	for(short i=1; i<=n; ++i) cin >> a[i];
	cin >> m;
	for(short i=1; i<=m; ++i) cin >> b[i];

	solve();

	return 0;
}

