#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 10100

struct node
{
	int p, d;
}
A[maxl];

int n;

bool cmp(node A, node B)
{
	return A.d > B.d || (A.d == B.d && A.p > B.p);
}

void solve()
{
	for(int i=0; i<n; ++i) scanf("%d%d", &A[i].p, &A[i].d);

	sort(A, A+n, cmp);

	int ans = 0;
	for(int i=0; i<n; ++i)
	{
		if(i == 0 || A[i].d != A[i-1].d) ans += A[i].p;
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		solve();
	}
	return 0;
}

