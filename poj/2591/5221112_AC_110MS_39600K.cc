#include <stdio.h>
#define MaxL 10000001

int f[MaxL+10];

void init()
{
	f[0] = 0;
	int p2=0, p3=0, p=0;
	while(p < MaxL)
	{
		int a = 2 * f[p2] + 1;
		int b = 3 * f[p3] + 1;
		if(a < b)
		{
			f[++p] = a;
			p2++;
		}
		else if(a > b)
		{
			f[++p] = b;
			p3++;
		}
		else
		{
			f[++p] = a;
			p2++, p3++;
		}
	}
}

int main()
{
	int n;
	init();
	while(scanf("%d", &n)!=EOF) printf("%d\n", f[n]);
	return 0;
}