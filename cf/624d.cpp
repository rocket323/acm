#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define maxl 1000010
#define INF 1e16
#define ll long long
#define min(a, b) ((a) < (b) ? (a) : (b))

int n, a, b, x[maxl], p[maxl], top;
ll f[2][3][100];

void Prime(int n)
{
	for(int i = 2; (ll)i * i <= n; ++i)
	{
		if(n % i == 0)
		{
			p[top++] = i;
			while(n % i == 0) n /= i;
		}
	}
	if(n > 1) p[top++] = n;
}

ll Process()
{
	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 3; ++j)
			for(int k = 0; k < top; ++k)
				f[0][j][k] = INF;

	for(int i = 0; i < top; ++i)
	{
		if((x[1] - 1) % p[i] == 0) f[0][0][i] = b;
		if((x[1] + 1) % p[i] == 0) f[0][0][i] = b;
		if(x[1] % p[i] == 0) f[0][0][i] = 0;
	}

	int idx = 0;
	for(int i = 1; i < n; ++i)
	{
		for(int j = 0; j < top; ++j) for(int k = 0; k < 3; ++k) f[idx^1][k][j] = INF;

		for(int j = 0; j < top; ++j)
		{
			if(f[idx][0][j] < INF)
			{
				if((x[i+1] - 1) % p[j] == 0) f[idx^1][0][j] = min(f[idx^1][0][j], f[idx][0][j] + b);
				if((x[i+1] + 1) % p[j] == 0) f[idx^1][0][j] = min(f[idx^1][0][j], f[idx][0][j] + b);
				if(x[i+1] % p[j] == 0) f[idx^1][0][j] = min(f[idx^1][0][j], f[idx][0][j]);
				f[idx^1][1][j] = min(f[idx^1][1][j], f[idx][0][j] + a);
			}

			if(f[idx][1][j] < INF)
			{
				if((x[i+1] - 1) % p[j] == 0) f[idx^1][2][j] = min(f[idx^1][2][j], f[idx][1][j] + b);
				if((x[i+1] + 1) % p[j] == 0) f[idx^1][2][j] = min(f[idx^1][2][j], f[idx][1][j] + b);
				if(x[i+1] % p[j] == 0) f[idx^1][2][j] = min(f[idx^1][2][j], f[idx][1][j]);
				f[idx^1][1][j] = min(f[idx^1][1][j], f[idx][1][j] + a);
			}

			if(f[idx][2][j] < INF)
			{
				if((x[i+1] - 1) % p[j] == 0) f[idx^1][2][j] = min(f[idx^1][2][j], f[idx][2][j] + b);
				if((x[i+1] + 1) % p[j] == 0) f[idx^1][2][j] = min(f[idx^1][2][j], f[idx][2][j] + b);
				if(x[i+1] % p[j] == 0) f[idx^1][2][j] = min(f[idx^1][2][j], f[idx][2][j]);
			}
		}
		idx ^= 1;
	}

	ll ans = INF;
	for(int j = 0; j < top; ++j)
		for(int k = 0; k < 3; ++k)
			ans = min(ans, f[idx][k][j]);

	return ans;
}

int main()
{
	while(scanf("%d%d%d", &n, &a, &b) != EOF)
	{
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", &x[i]);
		}
		top = 0;
		Prime(x[1]);
		Prime(x[1] - 1);
		Prime(x[1] + 1);
		Prime(x[n]);
		Prime(x[n] - 1);
		Prime(x[n] + 1);
		sort(p, p + top);
		top = unique(p, p + top) - p;

		//for(int i = 0; i < top; ++i) printf("%d: %d\n", i, p[i]);

		ll ans1 = Process();
		reverse(x + 1, x + n + 1);
		ll ans2 = Process();

		cout << min(ans1, ans2) << endl;
	}

	return 0;
}

