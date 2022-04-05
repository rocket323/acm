#include <stdio.h>
#include <cstring>
#define maxl 10000

int f[maxl + 10];

int main()
{
	memset(f, 0, sizeof f);

	for(int i=1; i<=maxl; ++i)
	{
		int sum = i, k = i;
		while(k)
		{
			sum += k % 10;
			k /= 10;
		}
		if(sum <= maxl) f[sum] = 1;
	}

	for(int i=1; i<=maxl; ++i)
	{
		if(!f[i]) printf("%d\n", i);
	}

	return 0;
}

