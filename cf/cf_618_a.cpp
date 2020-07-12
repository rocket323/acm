#include <stdio.h>
#define maxl 100010
#define ll long long

int f[maxl], n;;

int main()
{
	f[1] = 1;
	for(int i = 2; i <= 20; ++i)
	{
		f[i] = 2 * f[i - 1];
	}

	while(scanf("%d", &n) != EOF)
	{
		int a[100], top = 0;
		for(int i = 20; i >= 1; --i)
		{
			if(f[i] <= n)
			{
				a[top++] = i;
				n -= f[i];
			}
		}
		for(int i = 0; i < top; ++i) printf("%d%c", a[i], (i == top - 1) ? '\n' : ' ');
	}

	return 0;
}

