#include <stdio.h>
#include <cstring>
#define INF 0x3f3f3f3f
#define max(a,b) ((a>b)?a:b)

int num[200], n, A[200], top, f[200][200];
char s[200][2];

int dp(int a, int b)
{
	for(int i=a; i<=b; ++i) f[i][i] = num[i];

	for(int l=2; l<=n; ++l)
	{
		for(int i=a, j=i+l-1; j<=b; ++i, ++j)
		{
			f[i][j] = -(1<<30);
			for(int k=i+1; k<=j; ++k)
			{
				int tmp = 0;
				if(s[k][0] == 't') tmp = f[i][k-1] + f[k][j];
				else tmp = f[i][k-1] * f[k][j];
				f[i][j] = max(f[i][j], tmp);
			}
		}
	}
	return f[a][b];
}

void solve()
{
	for(int i=1; i<=n; ++i)
	{
		scanf("%s%d", s[i], &num[i]);
		strcpy(s[i+n], s[i]);
		num[i+n] = num[i];
	}

	int ans = -(1<<30);
	top = 0;
	for(int i=1; i<=n; ++i)
	{
		int tmp = dp(i, i+n-1);
		if(tmp > ans)
		{
			ans = tmp;
			A[top = 1] = i;
		}
		else if(tmp == ans)
		{
			A[++top] = i;
		}
	}

	printf("%d\n", ans);
	for(int i=1; i<=top; ++i) printf("%d%c", A[i], (i==top)? '\n' : ' ');
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		solve();
	}
	return 0;
}

