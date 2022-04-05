#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int f[205][205], n, m;

int mex(int list[], int top)
{
	if(top == 0) return 0;
	sort(list, list + top);
	if(list[0] != 0) return 0;
	for(int i=1; i<top; ++i) if(list[i] > list[i-1] + 1) return list[i-1] + 1;
	return list[top - 1] + 1;
}

int sg(int n, int m)
{
	if(n > m) swap(n, m);
	if(f[n][m] != -1) return f[n][m];
	if(n <= 3 && m <= 3) return f[n][m] = 0;

	int list[200], top = 0;
	for(int i=2; i<n-1; ++i) list[top++] = sg(i, m) ^ sg(n - i, m);
	for(int i=2; i<m-1; ++i) list[top++] = sg(n, i) ^ sg(n, m - i);

	return f[n][m] = mex(list, top);
}

int main()
{
	memset(f, -1, sizeof f);
	while(scanf("%d%d", &n, &m) != EOF)
	{
		if(n > m) swap(n, m);
		if(n == 1) puts("WIN");
		else
		{
			int k = sg(n, m);
			if(k) puts("WIN");
			else puts("LOSE");
		}
	}
	return 0;
}

