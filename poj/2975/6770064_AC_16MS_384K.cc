#include <stdio.h>
#include <cstring>
#include <math.h>
#include <algorithm>
using namespace std;

int n, a[1010];

int main()
{
	int t, up;
	while(scanf("%d", &n), n)
	{
		up = 0;
		for(int i=0; i<n; ++i)
		{
			scanf("%d", &a[i]);
			up = max(up, (int)ceil(log(a[i] * 1.0) / log(2.0)));
		}

		int k;
		for(int i=up; i>=0; --i)
		{
			k = 0;
			for(int j=0; j<n; ++j)
			{
				if(a[j] & (1<<i)) k++;
			}
			if(k & 1)
			{
				printf("%d\n", k);
				break;
			}
		}
		if(!(k & 1)) puts("0");
	}
	return 0;
}

