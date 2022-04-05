#include <stdio.h>
#include <cstring>
#define maxl 10010

int t[maxl], ft[maxl], st[maxl], sf[maxl], f[maxl];
int n, s, Q[maxl], head, tail;

void init()
{
	scanf("%d", &s);
	for(int i=1; i<=n; ++i) scanf("%d%d", &t[i], &ft[i]);
	st[n+1] = sf[n+1] = 0;
	for(int i=n; i>=1; --i)
	{
		st[i] = st[i+1] + t[i];
		sf[i] = sf[i+1] + ft[i];
	}
}

double slope(int i, int j)
{
	return (f[i] - f[j]) * 1.0 / (st[i] - st[j]);
}

void solve()
{
	tail = 1;
	Q[head = 0] = n + 1;
	f[n + 1] = 0;

	for(int i=n; i>=1; --i)
	{
		while(tail - head > 1 && slope(Q[head], Q[head+1]) <= sf[i]) head++;

		int k = Q[head];
		f[i] = f[k] + (s + st[i] - st[k]) * sf[i];

		while(tail - head > 1 && slope(Q[tail-2], Q[tail-1]) >= slope(Q[tail-1], i)) tail--;
		Q[tail++] = i;
	}
	printf("%d\n", f[1]);
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

