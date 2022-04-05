#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#define eps 1e-8
#define two(x) ((x) * (x))

double f[1010], pl, pr;
int n;

double fun(double p)
{
	return p / (1 - p) / (1 - p);
}

int main()
{
	while(scanf("%d%lf%lf", &n, &pl, &pr) == 3)
	{
		f[0] = 0.0;
		//f[1] = 1 / (1 - pl - pr);
		for(int i=1; i<=n; ++i)
		{
			f[i] = 1e20;
			for(int j=0; j<i; ++j)
			{
				double tmp = f[j] + f[i-j-1] + 1;
				//double tmp = 0.0;
				//printf("%d %d %lf\n", i, j, tmp);
				double p1 = pl / (1 - pr);
				double p2 = pr / (1 - pl);

				double k = (1 - pl - pr) * ((f[j] + 1) / (1 - pr) * fun(p1) + (f[i - j - 1] + 1) / (1 - pl) * fun(p2));

				tmp += k;
				if(tmp < f[i]) f[i] = tmp;
			}
		}
		printf("%.2lf\n", f[n]);
	}
	return 0;
}
