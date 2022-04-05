/*
 * POJ3074 
 * Sodoku solved with Dancing Links
 */
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

////////////////////////////////////////////////////////////////////////

#define MAXSIZE 100010
#define MAXROW 750
#define MAXCOL 650

char str[100];
int num[MAXROW], A[MAXROW][MAXCOL], rr[MAXROW], cc[MAXCOL];
int U[MAXSIZE], D[MAXSIZE], L[MAXSIZE], R[MAXSIZE], idx;
int row[MAXSIZE], col[MAXSIZE], head;

//每行的表头，每列的表头, 每列的1的个数
int hr[MAXROW], hc[MAXCOL], cnt[MAXCOL];

int n, m;
int ans[MAXROW], top, flag;

//初始化n * m 的矩阵
void init(int n, int m)
{
	memset(cnt, 0, sizeof cnt);

	idx = 0;
	head = idx++;
	L[head] = R[head] = U[head] = D[head] = head;

	for(int i=1; i<=n; ++i)
	{
		hr[i] = idx++;
		L[hr[i]] = R[hr[i]]= U[hr[i]] = D[hr[i]] = hr[i];
		row[hr[i]] = i; col[hr[i]] = -1;
	}
	for(int i=1; i<=m; ++i)
	{
		hc[i] = idx++;
		col[hc[i]] = i; row[hc[i]] = -1;

		U[hc[i]] = D[hc[i]] = L[hc[i]] = R[hc[i]] = hc[i];

		if(i > 1) L[hc[i]] = hc[i-1];
		else L[hc[i]] = head;
		if(i < m) R[hc[i]] = hc[i] + 1;
		else R[hc[i]] = head;

		R[L[hc[i]]] = L[R[hc[i]]] = hc[i];
	}
}

//在第r行，第c列添加一个1
void addNode(int r, int c)
{
	int nd = idx++;

	row[nd] = r;
	col[nd] = c;

	L[nd] = L[hr[r]];
	R[nd] = hr[r];
	R[L[nd]] = L[R[nd]] = nd;

	U[nd] = U[hc[c]];
	D[nd] = hc[c];
	D[U[nd]] = U[D[nd]] = nd;

	cnt[c]++;
}

//覆盖第c列
void cover(int c)
{
	if(c == -1) return;
	L[R[hc[c]]] = L[hc[c]];
	R[L[hc[c]]] = R[hc[c]];

	for(int i=D[hc[c]]; i!=hc[c]; i=D[i])
	{
		for(int j=R[i]; j!=i; j=R[j])
		{
			D[U[j]] = D[j];
			U[D[j]] = U[j];
			cnt[col[j]]--;
		}
	}
}

//恢复第c列
void resume(int c)
{
	if(c == -1) return;
	for(int i=U[hc[c]]; i!=hc[c]; i=U[i])
	{
		for(int j=L[i]; j!=i; j=L[j])
		{
			D[U[j]] = j;
			U[D[j]] = j;
			cnt[col[j]]++;
		}
	}
	L[R[hc[c]]] = R[L[hc[c]]] = hc[c];
}

void out()
{
	for(int i=0; i<top; ++i)
	{
		int idx = ans[i];
		int r = rr[idx], c = cc[idx], x = num[idx];
		str[(r-1) * 9 + c - 1] = '0' + x;
	}
	puts(str);
}

void dfs()
{
	if(flag) return;
	if(R[head] == head)
	{
		flag = 1;
		out();
		return;
	}

	int min = MAXROW, c = -1;
	
	for(int i=R[head]; i!=head; i=R[i])
	{
		if(cnt[col[i]] < min)
		{
			min = cnt[col[i]];
			c = i;
		}
	}

	cover(col[c]);

	for(int i=D[c]; i!=c; i=D[i])
	{
		ans[top++] = row[i];
		for(int j=R[i]; j!=i; j=R[j]) cover(col[j]);
		dfs();
		if(flag) return;

		top--;
		for(int j=L[i]; j!=i; j=L[j]) resume(col[j]);
	}

	resume(col[c]);
}

void solve(int n, int m, int A[][MAXCOL])
{
	/*
	printf("%d %d\n", n, m);
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j) printf("%d ", A[i][j]);
		puts("");
	}
	*/

	init(n, m);

	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j) if(A[i][j]) addNode(i, j);
	}

	top = 0;
	flag = 0;
	dfs();

	if(!flag) puts("NO");
}

////////////////////////////////////////////////////////////////////////


/*
 * 模型说明：
 * 一个N * M的矩阵，N <= 9*9*9 = 729，M = 9*9*4 = 324
 * 一个行用一个三元组(r, c, k)表示格子(r, c)放数字k
 *
 * 第一个9*9列约束每一行有且只有一个数字
 * 第二个9*9列约束每一列有且只有一个数字
 * 第三个9*9列约束每一格子有且只有一个数字
 * 第四个9*9列约束每一块有且只有一个数字
 */

int calc(int r, int c)
{
	return (r / 3) * 3 + (c / 3);
}

void addRow(int r, int c, int k)
{
	++n;
	num[n] = k;
	rr[n] = r;
	cc[n] = c;

	int c1 = (r - 1) * 9 + k;
	int c2 = 81 * 1 + (c - 1) * 9 + k;
	int c3 = 81 * 2 + (r - 1) * 9 + c;
	int c4 = 81 * 3 + calc(r - 1, c - 1) * 9 + k;

	A[n][c1] = A[n][c2] = A[n][c3] = A[n][c4] = 1;
}

int main()
{
	while(gets(str), str[0] != 'e')
	{
		n = 0;
		memset(A, 0, sizeof A);
		for(int i=1; i<=9; ++i)
		{
			for(int j=1; j<=9; ++j)
			{
				int idx = (i - 1) * 9 + j - 1;

				if(str[idx] == '.') for(int k=1; k<=9; ++k) addRow(i, j, k);
				else addRow(i, j, str[idx] - '0');
			}
		}
		solve(n, 9*9*4, A);
	}
	return 0;
}

