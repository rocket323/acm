#include <stdio.h>
#include <cstring>

int n, m, sum, a;

int main()
{
	scanf("%d%d", &n, &m);
	sum = 0;
	for(int i=0; i<m; ++i)
	{
		scanf("%d", &a);
		sum += (a % n);
	}
	printf("%d\n", sum % n);

	return 0;
}

