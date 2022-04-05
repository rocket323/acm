#include <stdio.h>
#include <cstring>

int n, a, p, q, ans;
int A[100], top;

int gcd(int a, int b)
{
	if(!b) return a;
	else return gcd(b, a % b);
}

int min(int a, int b){ return (a < b) ? a : b; }

void minus(int a, int b, int c, int d, int& e, int& f)
{
	e = a * d - b * c;
	f = b * d;

	int x = gcd(e, f);
	e /= x;
	f /= x;
}

void dfs(int p, int q, int cnt, int start, int pro)
{
	if(p == 0)
	{
		ans++;
		//for(int i=0; i<top; ++i) printf("%d ", A[i]);
		//puts("");
		return;
	}
	if((n - cnt) * q < start * p) return;
	//if(cnt == n) return;

	//int end = a / pro;
	int end = min((n - cnt) * q / p, a / pro);
	while(q - start * p > 0) start++;
	for(int i=start; i<=end; ++i)
	{
		int a = -1, b = -1;
		minus(p, q, 1, i, a, b);
		if(a < 0) continue;
		dfs(a, b, cnt + 1, i, pro * i);
	}
}

int main()
{
	while(scanf("%d%d%d%d", &p, &q, &a, &n), (p + q + a + n))
	{
		ans = 0;
		dfs(p, q, 0, 1, 1);
		printf("%d\n", ans);
	}
	return 0;
}

