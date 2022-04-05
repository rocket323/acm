#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int f[205][205], n, m;

int mex(vector<int> list)
{
	sort(list.begin(), list.end());
	list.push_back(10000000);
	if(list[0] != 0) return 0;
	int n = list.size();
	for(int i=1; i<n; ++i) if(list[i] > list[i-1] + 1) return list[i-1] + 1;
}

int sg(int n, int m)
{
	if(n > m) swap(n, m);
	if(f[n][m] != -1) return f[n][m];
	if(n <= 3 && m <= 3) return f[n][m] = 0;

	vector<int> list;
	list.clear();
	for(int i=1; i<n; ++i) list.push_back(sg(i, m) ^ sg(n - i, m));
	for(int i=1; i<m; ++i) list.push_back(sg(n, i) ^ sg(n, m - i));

	return f[n][m] = mex(list);
}

int main()
{
	memset(f, -1, sizeof f);
	while(scanf("%d%d", &n, &m) != EOF)
	{
		if(n > m) swap(n, m);
		int k = sg(n, m);
		if(k) puts("WIN");
		else puts("LOSE");
	}
	return 0;
}

