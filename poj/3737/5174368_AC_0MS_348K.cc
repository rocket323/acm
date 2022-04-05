#include <stdio.h>
#include <cmath>
#define pi (acos(-1))

void solve(double s)
{
	double r = 0.5 * sqrt(s / pi);
	double h = 2 * sqrt(2) * r;
	double v = 1.0 / 3 * pi * r * r * h;
	printf("%.2f\n%.2f\n%.2f\n", v, h, r);
}

int main()
{
	double s;
	while(scanf("%lf", &s)!=EOF)
	{
		solve(s);
	}
	return 0;
}