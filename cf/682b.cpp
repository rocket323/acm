#include <stdio.h>
#include <cstring>
#include <algorithm>
#define maxl 100010

using namespace std;

int n;
int a[maxl];

int main()
{
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
		sort(a, a + n);

		int last = 0;
		for (int i = 0; i < n; ++i)
		{
			if (a[i] <= last) continue;
			last++;
		}
		printf("%d\n", last + 1);
	}

	return 0;
}

