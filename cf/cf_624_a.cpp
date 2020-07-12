#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
	double d, l, v1, v2;
	while(cin >> d >> l >> v1 >> v2)
	{
		double ans = (l - d) / (v1 + v2);
		printf("%.8lf\n", ans);
	}

	return 0;
}

