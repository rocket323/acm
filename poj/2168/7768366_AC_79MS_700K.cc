/*
 * =======================================================
 *       Filename:  2168.cpp
 *    Description:  
 *        Created:  20/10/10 20:34:32
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define maxl 20010
#define INF 0x3f3f3f3f

struct node
{
	int a, b, id;
}
E[maxl];

int n, f[maxl], lst[maxl], p[maxl], lie[maxl], top;
vector<int> ret;

bool cmp(node A, node B)
{
	return A.b < B.b || A.b == B.b && A.a < B.a;
}

void init()
{
	ret.clear();
	top = 0;
	for(int i=1; i<=n; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		if(a + b + 1 > n)
		{
			ret.push_back(i);
			continue;
		}
		top++;
		E[top].a = a + 1;
		E[top].b = n - b;
		E[top].id = i;
	}

	if(top) sort(E + 1, E + 1 + top, cmp);
}

void solve()
{
	memset(f, 0x3f, sizeof f);
	for(int i=0; i<=n; ++i) p[i] = -1;
	f[0] = 0;

	for(int i=1; i<=top; ++i)
	{
		if(i == 1 || !(E[i].a == E[i-1].a && E[i].b == E[i-1].b)) lst[i] = i;
		else lst[i] = lst[i-1];
		if(i - lst[i] > E[i].b - E[i].a) lst[i] = i - (E[i].b - E[i].a);
	}

	E[0].b = -10000;

	int ans = INF, pos = -1;
	for(int i=1; i<=top; ++i)
	{

		int x = lst[i] - 1;

		for(int j=x; j>=0; --j)
		{
			if(E[j].b >= E[i].a) continue;
			int tmp = f[j] + x - j;
			if(tmp < f[i])
			{
				f[i] = tmp;
				p[i] = j;
			}
		}

		if(f[i] + top - i < ans)
		{
			ans = f[i] + top - i;
			pos = i;
		}
	}

	if(pos != -1)
	{
		for(int i=pos+1; i<=top; ++i) ret.push_back(E[i].id);
		while(pos != 0)
		{
			for(int j=lst[pos]-1; j>p[pos]; --j) ret.push_back(E[j].id);
			pos = p[pos];
		}
	}
	if(ret.size() > 0) sort(ret.begin(), ret.end());

	printf("%d", (int)ret.size());
	for(int i=0; i<ret.size(); ++i) printf(" %d", ret[i]);
	puts("");
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

