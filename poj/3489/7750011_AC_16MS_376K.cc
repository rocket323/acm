#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	int num, n, x, k;
	while(scanf("%d%d%d", &n, &x, &k) != EOF)
	{
		int d = -1;
		for(int i=1; i<=n; ++i)
		{
			scanf("%d", &num);
			while(num % k == 0) num /= k;
			if(d == -1) d = num;
			else d = __gcd(d, num);
		}
		if(x % d) puts("No");
		else puts("Yes");
	}
	return 0;
}

