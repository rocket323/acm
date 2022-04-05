#include <stdio.h>
#include <cstring>

int A[100], B[100], lt, top, n, a[100];
int tot, sum;

int diff(int A[], int sa, int B[], int sb)
{
	if(sa != sb) return 1;
	for(int i=0; i<sa; ++i) if(A[i] != B[i]) return 1;
	return 0;
}

void out(int A[], int top)
{
	printf("%d", A[0]);
	for(int i=1; i<top; ++i) printf("+%d", A[i]);
	puts("");
}

void dfs(int idx, int now)
{
	if(now == 0 && top != 0)
	{
		if(tot == 0 || diff(A, lt, B, top))
		{
			out(B, top);
			lt = top;
			for(int i=0; i<top; ++i) A[i] = B[i];
		}
		tot = 1;
		return;
	}

	if(idx == n + 1) return;

	for(int i=idx; i<=n; ++i)
	{
		if(i > idx && a[i] == a[i-1]) continue;
		if(now >= a[i])
		{
			B[top++] = a[i];
			dfs(i + 1, now - a[i]);
			top--;
		}
	}
}

void solve()
{
	printf("Sums of %d:\n", sum);
	tot = 0;

	top = 0;
	dfs(1, sum);

	if(tot == 0) puts("NONE");
}

int main()
{
	while(scanf("%d%d", &sum, &n) && (sum + n))
	{
		for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
		solve();
	}
	return 0;
}

