#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;
#include <math.h>
#define maxl 105
#define eps 1e-8

int n;
int x[maxl];
double p[maxl], q[maxl];

double Process()
{
	double ans = n;
	for(int i = 1; i <= n; ++i) ans *= p[i];

	for(int i = 1; i <= 100; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			double now = 1.0;
			for(int k = 1; k <= n; ++k)
			{
				if(k < j)
				{
					now *= (1.0 - pow(q[k], (i + 1)));
				}
				else if(k > j)
				{
					now *= (1.0 - pow(q[k], i));
				}
				else
				{
					now *= pow(q[k], i) * p[k];
				}
			}
			now *= (i * n + j);
			//printf("%d %d: %lf\n", i, j, now);
			if(now < eps) return ans;
			ans += now;
		}
	}
	return ans;
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		for(int i = 1; i <= n; ++i) scanf("%d", &x[i]);
		//sort(x + 1, x + 1 + n, greater<int>());
		sort(x + 1, x + 1 + n);
		
		for(int i = 1; i <= n; ++i)
		{
			p[i] = x[i] / 100.0;
			q[i] = 1.0 - p[i];
		}
		printf("%.8lf\n", Process());
	}

	return 0;
}

