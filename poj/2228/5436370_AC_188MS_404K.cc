#include <stdio.h>
#include <cstring>
#define MaxL 3831
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)

int n, b;
int f[2][MaxL][2], u[MaxL];

void solve()
{
	int ans1 = 0, ans2 = 0, idx;

	memset(f, 0, sizeof f);
	idx = 0;

	for(int i=2; i<n; ++i)
	{
		idx ^= 1;
		memset(f[idx], 0, sizeof f[idx]);
		for(int j=1; j<=min(b, i); ++j)
		{
			f[idx][j][1] = max(f[idx][j][1], f[idx^1][j-1][0]);
			if(j>1) f[idx][j][1] = max(f[idx][j][1], f[idx^1][j-1][1] + u[i]);

			f[idx][j][0] = max(f[idx][j][0], f[idx^1][j][0]);
			f[idx][j][0] = max(f[idx][j][0], f[idx^1][j][1]);

			//printf("%d %d %d %d\n", i, j, f[idx][j][0], f[idx][j][1]);
		}
	}

	//printf("%d %d\n", f[idx][b][0], f[idx][b][1]);

	ans1 = max(f[idx][b][0], f[idx][b][1]);

	memset(f, 0, sizeof f);
	idx = 0;
	f[0][1][1] = u[1];

	for(int i=2; i<n; ++i)
	{
		idx ^= 1;
		memset(f[idx], 0, sizeof f[idx]);

		for(int j=1; j<=min(b, i); ++j)
		{
			f[idx][j][1] = max(f[idx][j][1], f[idx^1][j-1][0]);
			if(j>1) f[idx][j][1] = max(f[idx][j][1], f[idx^1][j-1][1] + u[i]);

			f[idx][j][0] = max(f[idx][j][0], f[idx^1][j][0]);
			f[idx][j][0] = max(f[idx][j][0], f[idx^1][j][1]);
		}
	}
	ans2 = max(f[idx][b-1][0], f[idx][b-1][1] + u[0]);
	
	//printf("%d %d\n", f[idx][b-1][0], f[idx][b-1][1] + u[0]);

	printf("%d\n", max(ans1, ans2));
}

int main()
{
	scanf("%d%d", &n, &b);
	for(int i=0; i<n; ++i) scanf("%d", &u[i]);
	//for(int i=0; i<n; ++i) printf("%d ", u[i]);
	//puts("");
	solve();
	return 0;
}

