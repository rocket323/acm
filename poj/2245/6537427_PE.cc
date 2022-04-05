#include <stdio.h>
#include <cstring>

int n, A[100], top, a[100];

void dfs(int now)
{
	if(top == 6)
	{
		for(int i=0; i<6; ++i) printf("%d%c", A[i], (i==5)?'\n':' ');
		return;
	}
	if(now == n + 1) return;

	for(int i=now; i<=n; ++i)
	{
		A[top++] = a[i];
		dfs(i + 1);
		top--;
	}
}

int main()
{
	while(scanf("%d", &n), n)
	{
		for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
		top = 0;
		dfs(1);
	}
	return 0;
}

