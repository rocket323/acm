#include <stdio.h>
#include <cstring>

int c[200], n, cnt;

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		memset(c, 0, sizeof c);
		cnt = 0;
		for(int i=1; i<=n; ++i)
		{
			for(int j=i; j<=n; j+=i) c[j]++;
		}
		for(int i=1; i<=n; ++i) if(c[i] & 1) cnt++;
		printf("%d\n", cnt);
	}
	return 0;
}
