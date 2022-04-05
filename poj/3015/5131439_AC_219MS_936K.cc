#include <stdio.h>
#include <algorithm>
using namespace std;

double b[50010];
int n, m, a[50010];

bool cmp(int a, int b){ return a > b; }

void solve()
{
	sort(a+1, a+1+n, cmp);
	double now = 1.0, sum = 0.0, cnt = m+1-2, k = m+1-2;

	b[1] = m * 1.0 / n;
	for(int i=2; i<=n-m+1; ++i) b[i] = b[i-1] * (n-i+1-k) / (n-i+1);

	for(int i=n-m+1; i>=1; --i)
	{
		int x = a[i] - a[n+1-i];
		sum = sum + x * b[i];
	}
	printf("%.3f\n", sum);
}

int main()
{
	while(scanf("%d%d", &n, &m) && n)
	{
		for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
		solve();
	}
	return 0;
}