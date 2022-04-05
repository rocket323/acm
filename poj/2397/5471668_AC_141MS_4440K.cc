#include <stdio.h>
#include <cstring>
#define MaxL 1001
#define INF 0x3f3f3f3f

int s[MaxL], a[MaxL], n;
int f[MaxL][MaxL], p[MaxL][MaxL];
char w[MaxL];

void init()
{
	scanf("%d", &n);
	s[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &a[i]);
		s[i] = s[i-1] + a[i];
	}
}

void solve()
{
	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;

	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<=s[i]; ++j)
		{
			if(f[i][j]==INF) continue;

			int nh = j + a[i + 1], tmp = f[i][j];
			if(nh > f[i][j]) tmp = nh;
			//f[i+1][nh] = min(f[i+1][nh], tmp);
			if(tmp < f[i+1][nh])
			{
				f[i+1][nh] = tmp;
				p[i+1][nh] = j;
			}

			nh = j - a[i + 1], tmp = f[i][j];
			if(nh < 0) continue;

			//f[i+1][nh] = min(f[i+1][nh], tmp);
			if(tmp < f[i+1][nh])
			{
				f[i+1][nh] = tmp;
				p[i+1][nh] = j;
			}
		}
	}

	if(f[n][0]==INF)
	{
		puts("IMPOSSIBLE");
		return;
	}

	int h = 0;
	for(int i=n; i>0; --i)
	{
		if(p[i][h] > h) w[i] = 'D';
		else w[i] = 'U';
		h = p[i][h];
	}
	for(int i=1; i<=n; ++i) printf("%c", w[i]);
	puts("");
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
