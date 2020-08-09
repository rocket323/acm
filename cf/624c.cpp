#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#define maxl 505

int n, m, cnt[maxl];
int g[maxl][maxl];
char s[maxl];

bool dfs(int u, char ch)
{
	s[u] = ch;
	for(int v = 1; v <= n; ++v)
	{
		if(u == v) continue;
		if(g[u][v]) continue;
		//printf("u: %d, v: %d\n", u, v);

		if(s[v] != 0 && s[u] == s[v]) return false;
		char x = (ch == 'a') ? 'c' : 'a';
		if(s[v] != 0) continue;
		bool check = dfs(v, x);
		if(!check) return false;
	}
	return true;
}

bool CheckAgain()
{
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			if(i == j) continue;
			if(abs((int)s[i] - (int)s[j]) < 2)
			{
				if(g[i][j] == 0) return false;
			}
			else
			{
				if(g[i][j] == 1) return false;
			}
		}
	}
	return true;
}

int main()
{
	while(scanf("%d%d", &n, &m) != EOF)
	{
		int a, b;
		memset(g, 0, sizeof g);
		memset(s, 0, sizeof s);
		memset(cnt, 0, sizeof cnt);
		for(int i = 0; i < m; ++i)
		{
			scanf("%d%d", &a, &b);
			g[a][b] = 1;
			g[b][a] = 1;
			cnt[a]++;
			cnt[b]++;
		}

		bool check = true;
		for(int i = 1; i <= n; ++i)
		{
			bool tmp;
			if(s[i] == 0 && cnt[i] < n - 1)
			{
				tmp = dfs(i, 'a');
				if(!tmp) check = false;
			}
		}

		if(!check)
		{
			puts("No");
		}
		else
		{
			for(int i = 1; i <= n; ++i) if(s[i] == 0) s[i] = 'b';
			bool check = CheckAgain();
			if(!check)
			{
				puts("No");
				continue;
			}

			puts("Yes");
			puts(s + 1);
		}
	}

	return 0;
}

