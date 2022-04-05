#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

int cnt[200], n, m, c, q;
int l[200][200], r[200][200], u[200][200], d[200][200], len[200][200], col[200][200];

void update_len()
{
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) len[i][j] = min(min(l[i][j], r[i][j]), min(u[i][j], d[i][j])) - 1;
}

void calc(int idx, int tp, int A[][200])
{
	int sr, sc, dr, dc, lst_col = -1, lst_len = 0;
	if(tp == 1) sr = idx, sc = 1, dr = 0, dc = 1;
	else if(tp == 2) sr = idx, sc = m, dr = 0, dc = -1;
	else if(tp == 3) sr = 1, sc = idx, dr = 1, dc = 0;
	else if(tp == 4) sr = n, sc = idx, dr = -1, dc = 0;

	while(sr >= 1 && sr <= n && sc >= 1 && sc <= m)
	{
		if(col[sr][sc] == lst_col)
		{
			A[sr][sc] = --lst_len;
			sr += dr; sc += dc;
		}
		else
		{
			lst_len = 0;
			lst_col = col[sr][sc];
			int _r = sr, _c = sc;
			while(sr >= 1 && sr <= n && sc >= 1 && sc <= m && col[sr][sc] == lst_col)
			{
				lst_len++;
				sr += dr;
				sc += dc;
			}
			A[_r][_c] = lst_len;
			sr = _r + dr; sc = _c + dc;
		}
	}
}

void init()
{
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j) scanf("%d", &col[i][j]);
	}

	memset(cnt, 0, sizeof cnt);
	memset(len, 0x3f, sizeof len);
	memset(l, 0x3f, sizeof l);
	memset(r, 0x3f, sizeof r);
	memset(u, 0x3f, sizeof u);
	memset(d, 0x3f, sizeof d);

	for(int i=1; i<=n; ++i)
	{
		calc(i, 1, r);
		calc(i, 2, l);
	}

	for(int i=1; i<=m; ++i)
	{
		calc(i, 3, d);
		calc(i, 4, u);
	}
	update_len();
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j) cnt[col[i][j]] += len[i][j];
	}
}

void solve()
{
	char str[200];
	for(int x=0; x<q; ++x)
	{
		/*
		for(int i=1; i<=n; ++i)
		{
			for(int j=1; j<=m; ++j)
			{
				printf("%d ", len[i][j]);
			}
			puts("");
		}
		puts("");
		*/
		scanf("%s", str);
		if(str[0] == 'Q')
		{
			int t;
			scanf("%d", &t);
			printf("%d\n", cnt[t]);
		}
		else
		{
			int _r, _c, cl;
			scanf("%d%d%d", &_r, &_c, &cl);
			
			for(int i=1; i<=m; ++i) cnt[col[_r][i]] -= len[_r][i];
			for(int i=1; i<=n; ++i) cnt[col[i][_c]] -= len[i][_c];

			cnt[col[_r][_c]] += len[_r][_c];

			col[_r][_c] = cl;

			calc(_r, 1, r);
			calc(_r, 2, l);
			calc(_c, 3, d);
			calc(_c, 4, u);
			update_len();

			for(int i=1; i<=m; ++i) cnt[col[_r][i]] += len[_r][i];
			for(int i=1; i<=n; ++i) cnt[col[i][_c]] += len[i][_c];

			cnt[col[_r][_c]] -= len[_r][_c];
		}
	}
}

int main()
{
	while(scanf("%d%d%d%d", &n, &m, &c, &q) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

