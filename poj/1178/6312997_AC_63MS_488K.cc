#include <stdio.h>
#include <cstring>
#define INF 0x3f3f3f3f
#define id(r,c) ( (r) * 8 + (c) )
#define min(a,b) ((a<b)?a:b)

int ar[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int ac[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int br[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int bc[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int dk[100][100], dp[100][100];
int pr[100], pc[100], kr, kc, n;
char str[2000];
int Q[20000], head, tail, vis[100][100];

bool check(int r, int c)
{
	return (r >= 0 && r < 8 && c >= 0 && c < 8);
}

void dist(int sr, int sc, int ar[], int ac[], int d[][100], int key)
{
	d[id(sr, sc)][id(sr, sc)] = 0;
	tail = 1;
	Q[head = 0] = id(sr, sc);

	memset(vis, 0, sizeof vis);
	vis[sr][sc] = 1;

	while(head < tail)
	{
		int r = Q[head] / 8;
		int c = Q[head] % 8;

		for(int k=0; k<8; ++k)
		{
			int rr = r + ar[k];
			int cc = c + ac[k];
			if(check(rr, cc) && !vis[rr][cc])
			{
				Q[tail++] = id(rr, cc);
				vis[rr][cc] = 1;
				d[id(sr, sc)][id(rr, cc)] = d[id(sr, sc)][id(r, c)] + 1;
			}
		}
		head++;
	}
}

void init()
{
	kr = str[0] - 'A';
	kc = str[1] - '1';
	n = 0;
	for(int i=2; str[i]; i+=2)
	{
		pr[n] = str[i] - 'A';
		pc[n] = str[i+1] - '1';
		n++;
	}

	memset(dk, 0x3f, sizeof dk);
	memset(dp, 0x3f, sizeof dp);
	for(int i=0; i<8; ++i)
	{
		for(int j=0; j<8; ++j)
		{
			dist(i, j, br, bc, dp, 2);
			dist(i, j, ar, ac, dk, 1);
		}
	}
}

void solve()
{
	int ans = INF;

	for(int am=0; am<64; ++am)
	{
		for(int pk=0; pk<64; ++pk)
		{
			for(int i=0; i<n; ++i)
			{
				int tmp = dk[id(kr, kc)][pk] + dp[pk][am] + dp[id(pr[i], pc[i])][pk];

				for(int j=0; j<n; ++j)
				{
					if(i == j) continue;
					tmp += dp[id(pr[j], pc[j])][am];
				}

				ans = min(ans, tmp);
			}
		}
		int tmp = dk[id(kr, kc)][am];
		for(int i=0; i<n; ++i) tmp += dp[id(pr[i], pc[i])][am];
		ans = min(ans, tmp);
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%s", str) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

