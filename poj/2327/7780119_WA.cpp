#include <stdio.h>
#include <cstring>
#define two(x) ((x) * (x))

double f[1010], pl, pr;
int n;

int main()
{
	while(scanf("%d%lf%lf", &n, &pl, &pr) == 3)
	{
		f[0] = 0.0;
		for(int i=1; i<=n; ++i)
		{
			f[i] = 1e20;
			for(int j=0; j<i; ++j)
			{
				double tmp = f[j] + f[i-j-1] + 1;
				//double tmp = 0.0;
				//printf("%d %d %lf\n", i, j, tmp);
				double k = ((1-pr) * (f[j] + 1) + (1-pl) * (f[i-j-1] + 1) + 1) / two((1 - pl) * (1 - pr));
				//printf("%d %d %lf\n", i, j, k);
				tmp += k;
				if(tmp < f[i]) f[i] = tmp;
			}
			//printf("%d %lf\n", i, f[i]);
		}
		printf("%.2lf\n", f[n]);
	}
	return 0;
}
