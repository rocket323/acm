#include <stdio.h>
#include <cstring>

int f[20][20], num[5] = {2, 4, 16, 256, 65536};
int n;
bool mark[300];

void prepare()
{
	memset(f, -1, sizeof f);
	for(int i=0; i<16; ++i)
	{
		for(int j=0; j<16; ++j)
		{
			if(!i || !j) f[i][j] = 0;
			else
			{
				memset(mark, 0, sizeof mark);
				for(int a=0; a<i; ++a)
				{
					for(int b=0; b<j; ++b)
					{
						mark[f[a][j]^f[i][b]^f[a][b]] = 1;
					}
				}
				f[i][j] = 0;
				while(mark[f[i][j]]) f[i][j]++;
			}
		}
	}
}

int nim_mul(int x, int y)
{
	if(x < y)
	{
		x ^= y; y ^= x; x ^= y;
	}
	if(!y) return 0;
	if(x < 16 && y < 16) return f[x][y];

	int m = 0;

	for(; !((x >= num[m]) && (x < num[m+1])); ++m);
	m = num[m];
	int p = x / m, q = x % m, s = y / m, t = y % m;
	int c1 = nim_mul(p, s);
	int c2 = nim_mul(p, t) ^ nim_mul(q, s);
	int c3 = nim_mul(q, t);

	return ((c1 ^ c2) * m) ^ c3 ^ nim_mul(m / 2, c1);
}

int main()
{
	prepare();
	while(scanf("%d", &n) != EOF)
	{
		int sum = 0;
		for(int i=0; i<n; ++i)
		{
			int a, b, c, k;
			scanf("%d%d%d", &a, &b, &c);
			k = nim_mul(nim_mul(a, b), c);
			sum ^= k;
		}
		if(sum) puts("No");
		else puts("Yes");
	}
	return 0;
}

