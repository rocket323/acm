#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
#define INF 0x3f3f3f3f
using namespace std;

int n, m, sg[10010], s[105];
vector<int> list;

int mex(vector<int> list)
{
	list.push_back(INF);
	sort(list.begin(), list.end());

	if(list[0] != 0) return 0;

	for(int i=1; i<list.size(); ++i)
	{
		if(list[i] > list[i-1] + 1) return list[i-1] + 1;
	}
	return list.back() + 1;
}

void init()
{
	for(int i=0; i<m; ++i) scanf("%d", &s[i]);

	sg[0] = 0;
	for(int i=0; i<=10000; ++i)
	{
		list.clear();
		for(int j=0; j<m; ++j)
		{
			int k = i - s[j];
			if(k < 0) continue;
			list.push_back(sg[k]);
		}
		sg[i] = mex(list);
	}
}

void solve()
{
	int t, k, a, sum;
	scanf("%d", &t);
	for(int i=0; i<t; ++i)
	{
		scanf("%d", &k);
		sum = 0;
		for(int j=0; j<k; ++j)
		{
			scanf("%d", &a);
			sum ^= sg[a];
		}
		if(sum) printf("W");
		else printf("L");
	}
	puts("");
}

int main()
{
	while(scanf("%d", &m), m)
	{
		init();
		solve();
	}
	return 0;
}

