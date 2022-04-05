#include <stdio.h>
#include <cstring>

int n;

void solve()
{
	int m = n / 4;
	if(n % 4) m++;

	printf("Printing order for %d pages:\n", n);
	for(int i=1; i<=m; ++i)
	{
		printf("Sheet %d, front: ", i);

		int k = 4 * m + 1 - (2 * i - 1);
		if(k <= n) printf("%d, ", k);
		else printf("Blank, ");
		printf("%d\n", 2 * i - 1);

		printf("Sheet %d, back : ", i);

		k = 4 * m + 1 - (2 * i);
		printf("%d, ", 2 * i);
		if(k <= n) printf("%d\n", k);
		else printf("Blank\n");
	}
}

int main()
{
	while(scanf("%d", &n), n)
	{
		solve();
	}
	return 0;
}

