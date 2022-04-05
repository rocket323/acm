#include <stdio.h>
#include <cstring>

int k;
double p;

int main()
{
	while(scanf("%d%f", &k, &p) == 2)
	{
		double a = k / p;
		double b = k * (k + 1) / p / p - a;
		printf("%.3f %.3f\n", a, b);
	}
	return 0;
}

