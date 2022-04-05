#include <stdio.h>
#include <cstring>

int b[200], num[200], f[105][10010], p[105][10010], k;
char str[200];

void out(int dep, int now)
{
	printf("%d", p[dep][now]);

	if(dep == 1) return;

	int old = now - b[dep - 1] * p[dep][now];
	old = (old % k + k) % k;

	out(dep - 1, old);
}

int main()
{
	while(scanf("%s%d", str, &k) != EOF)
	{
		int len = strlen(str);
		for(int i=0; i<len; ++i) num[len - i] = str[i] - '0';

		b[0] = 1;
		for(int i=1; i<=101; ++i) b[i] = b[i-1] * 10 % k;

		memset(f, 0x3f, sizeof f);
		memset(p, -1, sizeof p);
		f[0][0] = 0;

		for(int i=1; i<=len; ++i)
		{
			for(int j=0; j<k; ++j)
			{
				for(int x=0; x<10; ++x)
				{
					if(i == len && x == 0) continue;
					int w = 1;
					if(x == num[i]) w = 0;
					//if(i == 1) printf("no %d\n", num[i]);

					int old = j - b[i - 1] * x;
					old = (old % k + k) % k;

					if(f[i-1][old] + w < f[i][j])
					{
						p[i][j] = x;
						f[i][j] = f[i-1][old] + w;
					}
				}
			}
		}

		out(len, 0);
		puts("");
	}
	return 0;
}

