#include <stdio.h>
#include <cstring>

int num[4] = {2, 6, 8, 4};
int to[10];
int add[5] = {0, 4, 3, 2, 1};
int a[5] = {1, 1, 2, 1, 4};
int r[5] = {1, 4, 4, 2, 4};

inline int fun(int n, int m)
{
	int c = (n - m + 1) / 5;
	if(c & 1) return 4;
	else return 1;
}

void go(int n, int m, int& k, int& c, int num)
{
	int mm = m + add[m % num];
	if(mm <= n)
	{
		k = (k * r[m % num] * a[n % num] * fun(n, mm + 1)) % num;
		c += (n / num - (m - 1) / num);
		go(n / num, mm / num, k, c, num);
	}
	else
	{
		for(int i=m; i<=n; ++i) k = (k * i) % num;
		return;
	}
}

int get2(int n)
{
	int ans = 0;
	while(n){ ans += n / 2; n /= 2; }
	return ans;
}

int solve(int n, int m)
{

	if(m == 0) return 1;

	int k = 1, c5 = 0;
	go(n, n - m + 1, k, c5, 5);

	int c2 = get2(n) - get2(n-m);

	if(k & 1) k += 5;
	int p = 0;
	while(num[p] != k) p++;

	if(c2 < c5) return 5;
	else if(c2 == c5)
	{
		p = (p + c5 - 1) % 4;
		return to[num[p]];
	}
	else
	{
		p = (p + c5) % 4;
		return num[p];
	}
}

int main()
{
	int n, m;
	to[2] = 1, to[4] = 7, to[6] = 3, to[8] = 9;
	while(scanf("%d %d", &n, &m) != EOF) printf("%d\n", solve(n, m));
	return 0;
}

