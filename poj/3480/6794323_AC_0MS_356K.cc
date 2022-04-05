#include <stdio.h>
#include <cstring>

int main()
{
	int t, sum, n, a, cnt;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		sum = cnt = 0;
		for(int i=0; i<n; ++i)
		{
			scanf("%d", &a);
			sum ^= a;
			cnt += (a > 1);
		}
		if(cnt == 0) printf((n & 1) ? "Brother" : "John");
		else printf((!sum) ? "Brother" : "John");
		puts("");
	}
	return 0;
}

