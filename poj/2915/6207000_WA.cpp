#include <stdio.h>
#include <cstring>
#define INF 0x3f3f3f3f
#define MaxL 205
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)
#define go(x) (((x)<m)?(m-(x)):1)

int n, m, cnt[MaxL], f[MaxL][MaxL][23], pre[MaxL];
char S[MaxL], T[MaxL];

void init()
{
	//scanf("%s", T);
	gets(T);

	for(int i=0; T[i]; ++i) if(!(T[i] >= 'A' && T[i] <= 'Z')) while(1);

	n = 0;
	int len = strlen(T);

	for(int i=0; T[i]; ++i)
	{
		n++;
		S[n] = T[i];
		cnt[n] = 1;
		while(i+1 < len && T[i+1] == T[i]){ i++; cnt[n]++; }
	}

	memset(pre, -1, sizeof pre);
	for(int i=1; i<=n; ++i)
	{
		pre[i] = -1;
		for(int j=i-1; j>=1 && pre[i]==-1; --j)
		{
			if(S[i] == S[j]) pre[i] = j;
		}
	}
}

void solve()
{
	memset(f, 0x3f, sizeof f);
	
	for(int i=1; i<=n; ++i)
	{
		for(int k=0; k<=m; ++k)
		{
			if(cnt[i] + k < m) f[i][i][k] = m - (cnt[i] + k);
			else if(k == 0) f[i][i][k] = 1;
			else f[i][i][k] = 0;
		}
	}

	//for(int i=1; i<=n; ++i) printf("%c %d\n", S[i], cnt[i]);

	for(int l=2; l<=n; ++l)
	{
		for(int i=1; i<=n-l+1; ++i)
		{
			int j = i + l - 1;
			for(int k=0; k<=m; ++k)
			{
				
				if(cnt[j] + k >= m && k != 0)
				{
					f[i][j][k] = f[i][j-1][0];
				}
				/*
				else
				{
				*/
					//int flag = 0;
					//if(i == 1 && j == 3 && k == 2) flag = 1;
					//if(i == 1 && j == 5 && k == 0) flag = 1;

					f[i][j][k] = min(f[i][j][k], f[i][j-1][0] + go(cnt[j] + k));

					int tmp = cnt[j] + k;
					if(tmp > m) tmp = m;

					for(int p=pre[j]; p>=i && p!=-1; p=pre[p])
					//for(int p=i; p<j; ++p)
					{
						//if(flag) printf("here : %d\n", tmp);
						//if(S[p] != S[j]) while(1);
						f[i][j][k] = min(f[i][j][k], f[i][p][tmp] + f[p+1][j-1][0]);

						//if(flag) printf("no %d %d\n", f[i][p][tmp], f[p+1][j-1][0]);
					}
				//}
			}
		}
	}

	//printf("n %d %d\n", f[1][3][2], f[4][4][0]);
	
	printf("%d\n", f[1][n][0]);
}

int main()
{
	//int t;
	//scanf("%d", &t);
	while(scanf("%d\n", &m) != EOF)
	{
		init();
		solve();
	}
	return 0;
}
