#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

int a, b;

int main()
{
	while(scanf("%d%d", &a, &b) != EOF)
	{
		if(a > b) swap(a, b);
		int k = b - a;
		int aa = floor(k * (sqrt(5.0) + 1) / 2.0);
		if(a == aa) puts("0");
		else puts("1");
	}
}

