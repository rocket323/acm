#include <stdio.h>
#include <cstring>

int k;
double p;

int main()
{
	while(scanf("%d%lf", &k, &p) == 2)
	{
		double a = k / p;
		double b = k * (k + 1) / p / p - a;
		printf("%.3lf %.3lf\n", a, b);
	}
	return 0;
}

