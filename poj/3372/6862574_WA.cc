#include <stdio.h>
#include <cstring>

int main()
{
	int n;
	while(scanf("%d", &n) != EOF)
	{
		int now = 1, step = 2;
		while(true)
		{
			now = (now + step);
			if(now >= n)
			{
				now %= n;
				break;
			}
			step++;
		}
		if(now == 2 || n <= 2) puts("YES");
		else puts("NO");
	}
	return 0;
}

