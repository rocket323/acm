#include <stdio.h>
#include <cstring>
#define M 10000000
#define min(a,b) ((a<b)?a:b)

int b, n, m;

int euler(int n)
{
	int ans = n;

	for(int i=2; (long long)i * i <= n; ++i)
	{
		if(n % i) continue;

		ans = ans / i * (i - 1);
		while(n % i == 0) n /= i;
	}
	if(n > 1) ans = ans / n * (n - 1);
	return ans;
}

int mod(long long a, int n)
{
	return (a < n) ? a : (n + a % n);
}

int pow(int a, int n, int m)
{
	if(n==0) return 1 % m;
	int tmp = pow(a, n/2, m);
	tmp = mod((long long)tmp * tmp, m);

	if(n & 1) tmp = mod((long long)tmp * a, m);

	return tmp;
}

int solve(int n, int m)
{
	if(n==0) return 1;

	int tmp = euler(m);
	int k = solve(n-1, tmp);

	return pow(b, k, m);
}

int main()
{
	int top = 0, A[10];
	while(scanf("%d", &b) && b)
	{
		scanf("%d%d", &n, &m);
		int k = solve(n, M) % M;
		top = 0;
		while(k){ A[top++] = k % 10; k /= 10; }

		for(int i=0; i<m-top; ++i) printf("0");
		for(int i=min(top-1, m-1); i>=0; --i) printf("%d", A[i]);
		puts("");
	}
	return 0;
}

