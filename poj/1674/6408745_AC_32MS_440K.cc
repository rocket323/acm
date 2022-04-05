#include <stdio.h>
#include <cstring>
#define ll long long
#define MaxL 10001

int n, a[MaxL], vis[MaxL];

void init()
{
	scanf("%d", &n);
	for(int i=0; i<n; ++i)
	{
		scanf("%d", &a[i]);
		a[i]--;
	}
}

void solve()
{
	for(int i=0; i<n; ++i) vis[i] = 0;

	int sum = 0;
	for(int i=0; i<n; ++i)
	{
		if(vis[i]) continue;
		int cnt = 0, j = i;
		while(!vis[j])
		{
			vis[j] = 1;
			cnt++;
			j = a[j];
		}
		sum += cnt - 1;
	}
	printf("%d\n", sum);
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

