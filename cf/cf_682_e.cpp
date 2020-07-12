#include <stdio.h>
#include <cstring>
#define maxl 5010
#define ll long long

ll s;
int n;
int x[maxl], y[maxl];

int main()
{
	while (scanf("%d%s", &n, &s) != EOF)
	{
		for (int i = 0; i < n; ++i)
			scanf("%d%d", &x[i], &y[i]);
	}

	return 0;
}

