#include <stdio.h>
#include <cstring>

char str[10][10];
char ans[3000], t[10];
char ch;
int len, n, q;

char get_ans(int a, int b)
{

	for(int i=1; i<=q; ++i)
	{
		int aa = a % n;
		int bb = b % n;
		if(str[aa][bb] == ' ') return 0;

		a /= n;
		b /= n;
	}

	return 1;
}

void solve()
{
	for(int i=0; i<len; ++i)
	{
		for(int j=0; j<len; ++j)
		{
			int k = get_ans(i, j);
			if(k) ans[j] = ch;
			else ans[j] = ' ';
			//printf("%d %d %d\n", i, j, k);
		}
		ans[len] = 0;
		puts(ans);
	}
}

int main()
{
	while(scanf("%d", &n), n)
	{
		gets(t);
		ch = ' ';
		for(int i=0; i<n; ++i)
		{
			gets(str[i]);
			for(int j=0; j<n; ++j) if(str[i][j] != ' ') ch = str[i][j];
		}
		scanf("%d", &q);
		gets(t);

		len = 1;
		for(int i=0; i<q; ++i) len *= n;
		solve();
	}

	return 0;
}

