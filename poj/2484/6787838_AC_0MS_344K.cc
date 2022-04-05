#include <stdio.h>

int main()
{
	int n;
	while(scanf("%d", &n), n)
	{
		if(n < 3) puts("Alice");
		else puts("Bob");
	}
	return 0;
}

