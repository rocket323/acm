#include <stdio.h>

int main()
{
	int t, a[2], c, n;
	
	scanf("%d", &t);
	while(t--)
	{
		a[0] = a[1] = 0;
		scanf("%d", &n);
		for(int i=0; i<n; ++i)
		{
			scanf("%d", &c);
			if(c) a[i & 1]++;
		}
		if(n & 1) puts("YES");
		else if(a[0] - a[1] > 1 || a[1] - a[0] > 1) puts("NO");
		else puts("YES");
	}
	return 0;
}

