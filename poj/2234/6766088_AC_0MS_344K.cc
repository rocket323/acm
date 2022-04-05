#include <stdio.h>
#include <cstring>

int main()
{
	int n, a, sum;
	while(scanf("%d", &n) != EOF)
	{
		sum = 0;
		for(int i=0; i<n; ++i)
		{
			scanf("%d", &a);
			sum ^= a;
		}
		if(sum == 0) puts("No");
		else puts("Yes");
	}
	return 0;
}

