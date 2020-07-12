#include <stdio.h>
#include <cstring>

int n, k;
int f[15][1025][105];
int g[1025];

void process()
{
	int m = (1 << n);
	memset(g, 0, sizeof g);
	for(int i=0; i<m; ++i)
	{
		int x = i;
		while(x)
		{
			if(x & 1) g[i]++;
			x >>= 1;
		}
	}

	memset(f, 0, sizeof f);
	f[0][0][0] = 1;
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<m; ++j)
		{
			for(int x=0; x<=k; ++x)
			{
				if(f[i][j][x] == 0) continue;

				f[i+1][j][x] += f[i][j][x];

				for(int y=0; y<n; ++y)
				{
					if(j & (1<<y)) continue;

					int cnt = g[j] + 1;
					if(cnt > k) continue;
					f[i+1][j | (1<<y)][cnt] += f[i][j][x];
				}
			}
		}
	}

	int ans = 0;
	for(int i=0; i<m; ++i)
	{
		ans += f[n][i][k];
	}
	printf("%d\n", ans);
}

int main()
{
	scanf("%d%d", &n, &k);
	process();
	return 0;
}

