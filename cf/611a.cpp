#include <stdio.h>
#include <cstring>

int d;
char a[100], b[100];

int main()
{
	while(scanf("%d%s%s", &d, a, b) != EOF)
	{
		if(b[0] == 'w')
		{
			if(d == 5 || d == 6) puts("53");
			else puts("52");
		}
		else
		{
			if(d <= 29) puts("12");
			else if(d == 30) puts("11");
			else puts("7");
		}
	}
	
	return 0;
}

