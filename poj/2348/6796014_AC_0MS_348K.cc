#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

int a, b;

int main()
{
	while(scanf("%d%d", &a, &b), (a && b))
	{
		if(a > b) swap(a, b);

		int c1 = 0, c2 = 0, tmp;
		while(a)
		{
			int k = b / a;
			if(k == 1) c1++;
			else
			{
				c2++;
				break;
			}
			tmp = a; a = b % a; b = tmp;
		}
		if(c2)
		{
			if(c1 % 2 == 0) puts("Stan wins");
			else puts("Ollie wins");
		}
		else
		{
			if(c1 % 2 == 1) puts("Stan wins");
			else puts("Ollie wins");
		}
	}
	return 0;
}

