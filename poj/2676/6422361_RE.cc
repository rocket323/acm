#include <stdio.h>
#include <cstring>

struct node
{
	int r, c, val, b;
}
E[100];

int top, flag, h[15][10], l[15][10], a[10][10], block[10][10];

void dfs(int now)
{
	if(flag) return;
	if(now == top)
	{
		flag = 1;
		return;
	}

	int r = E[now].r, c = E[now].c, b = E[now].b;
	for(int i=1; i<10; ++i)
	{
		if(!h[r][i] && !l[c][i] && !block[b][i])
		{
			E[now].val = i;
			h[r][i] = 1; l[c][i] = 1; block[b][i] = 1;
			dfs(now + 1);
			h[r][i] = 0; l[c][i] = 0; block[b][i] = 0;
			if(flag) return;
		}
	}
}

int calc_block(int r, int c)
{
	int br = r / 3;
	int bc = c / 3;
	return br * 3 + bc;
}

void solve()
{
	char str[21];
	memset(h, 0, sizeof h);
	memset(l, 0, sizeof l);
	for(int i=0; i<9; ++i)
	{
		scanf("%s", str);
		for(int j=0; j<9; ++j)
		{
			a[i][j] = str[j] - '0';
			h[i][a[i][j]] = 1;
			l[j][a[i][j]] = 1;

			int b = calc_block(i, j);
			block[b][a[i][j]] = 1;

			if(a[i][j] == 0)
			{
				E[top].r = i;
				E[top].b = b;
				E[top++].c = j;
			}
		}
	}

	flag = 0;
	dfs(0);

	for(int i=0; i<top; ++i) a[E[i].r][E[i].c] = E[i].val;

	for(int i=0; i<9; ++i)
	{
		for(int j=0; j<9; ++j) printf("%d", a[i][j]);
		puts("");
	}
}

int main()
{
	int t;
	scanf("%d", &t);

	while(t--)
	{
		solve();
	}
	return 0;
}

