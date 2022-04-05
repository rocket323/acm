#include <stdio.h>
#include <cstring>

int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};

int n, m;
char A[1000][1000];

bool test(int r, int c)
{
	return (r >= 0 && r < n && c >= 0 && c < m);
}

void solve()
{
	int d = 0, r = 0, c = -1, now = 0;

	memset(A, -1, sizeof A);
	for(int i=0; i<n * m; ++i)
	{
		while(!test(r + dr[d], c + dc[d]) || A[r+dr[d]][c+dc[d]] != -1) d = (d + 1) % 4;
		r = r + dr[d];
		c = c + dc[d];

		A[r][c] = now + 'A';
		now = (now + 1) % 26;
	}

	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<m; ++j) printf("   %c", A[i][j]);
		puts("");
	}
}

int main()
{
	while(scanf("%d%d", &n, &m) != EOF)
	{
		solve();
	}
	return 0;
}

