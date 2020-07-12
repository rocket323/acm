#include <stdio.h>
#include <string.h>
#include <map>
#include <iostream>
#include <math.h>
using namespace std;
#define maxl 100010
#define pi (acos(-1))

int n, x0, yy;
double dmin, dmax;

double dist(int x1, int y1, int x2, int y2)
{
	return sqrt( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) );
}

int main()
{
	while(scanf("%d%d%d", &n, &x0, &yy) != EOF)
	{
		dmin = 1e20;
		dmax = 0;
		for(int i = 0; i < n; ++i)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			double d = dist(x0, yy, x, y);
			if(d < dmin) dmin = d;
			if(d > dmax) dmax = d;
		}

		double ans = pi * (dmax * dmax - dmin * dmin);
		printf("%.8lf\n", ans);
	}

	return 0;
}

