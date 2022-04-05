#include <stdio.h>
#include <cstring>

int h, m;

int solve(int h, int m)
{
	if(m) return 0;
	if(h == 12) return 24;
	return (h + 12) % 24;
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d:%d", &h, &m);
		printf("%d\n", solve(h, m));
	}
	return 0;
}
