#include <stdio.h>
#include <cstring>

int f[160], n;

int check(int n, int m)
{
	int x = 0;
	for(int i=2; i<=n; ++i)
	{
		x = (x + m) % i;
		//printf("%d %d\n", i, x);
	}
	if(x == 0) return 1;
	else return 0;
}

int main()
{
	//check(3, 5);
	for(int i=3; i<150; ++i)
	{
		for(int j=2; ; ++j)
		{
			int k = check(i - 1, j);
			if(k)
			{
				f[i] = j;
				break;
			}
		}
	}

	while(scanf("%d", &n), n)
	{
		printf("%d\n", f[n]);
	}
	return 0;
}

