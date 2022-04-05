#include <stdio.h>
#include <cstring>

int b[100], n, a;

int main()
{
	while(true)
	{
		n = 0;
		while(scanf("%d", &a), a > 0)
		{
			b[n++] = a;
		}
		if(n == 0) break;

		int ans = 0;
		for(int i=0; i<n; ++i)
		{
			for(int j=0; j<n; ++j)
			{
				if(b[i] == b[j] * 2) ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

