#include <stdio.h>
#include <cstring>

int main()
{
	int t, a, b;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &a, &b);
		if(a >= b) puts("MMM BRAINS");
		else puts("NO BRAINS");
	}
	return 0;
}
