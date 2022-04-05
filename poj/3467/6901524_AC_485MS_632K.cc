#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

int cnt[105], n, m, c, q;
int l[105][105], r[105][105], u[105][105], d[105][105], len[105][105], col[105][105];

void update_len()
{
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) len[i][j] = min(min(l[i][j], r[i][j]), min(u[i][j], d[i][j])) - 1;
}

void calc(int idx, int tp, int A[][105])
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
	char str[105];
	for(int x=0; x<q; ++x)
	{
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

			for(int i=1; i<=m; ++i)
			{
				len[_r][i] = min(min(l[_r][i], r[_r][i]), min(u[_r][i], d[_r][i])) - 1;
				cnt[col[_r][i]] += len[_r][i];
			}
			for(int i=1; i<=n; ++i)
			{
				len[i][_c] = min(min(l[i][_c], r[i][_c]), min(u[i][_c], d[i][_c])) - 1;
				cnt[col[i][_c]] += len[i][_c];
			}

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

