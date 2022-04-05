#include <stdio.h>
#define MaxL 1100
#include <cstring>
#include <iostream>
using namespace std;

int a[MaxL][MaxL], C[MaxL][MaxL];
int n, m;
char s[5];

void init()
{
	scanf("%d%d", &n, &m);
	memset(C, 0, sizeof C);
}

int Max(int a, int b){ return (a>b)?a:b; }
int Min(int a, int b){ return (a<b)?a:b; }

int lowbit(int x){ return x & (-x); }

void add(int r, int c)
{
	r += 2; c += 2;
	while(r)
	{
		int tmp = c;
		while(tmp)
		{
			C[r][tmp] ^= 1;
			tmp -= lowbit(tmp);
		}
		r -= lowbit(r);
	}
}

int getSum(int r, int c)
{
	r += 2; c += 2;
	int ans = 0;
	while(r < n+5)
	{
		int tmp = c;
		while(tmp < n+5)
		{
			ans ^= C[r][tmp];
			tmp += lowbit(tmp);
		}
		r += lowbit(r);
	}
	return ans;
}

void solve()
{
	for(int i=0; i<m; ++i)
	{
		int r1, c1, r2, c2;
		scanf("%s", s);
		if(s[0]=='C')
		{
			scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
			add(Max(r1, r2), Max(c1, c2));
			add(Max(r1, r2), Min(c1-1, c2-1));
			add(Min(r1-1, r2-1), Max(c1, c2));
			add(Min(r1-1, r2-1), Min(c1-1, c2-1));
		}
		else
		{
			scanf("%d%d", &r1, &c1);
			printf("%d\n", getSum(r1, c1));
		}
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}
