#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

int a[1010], n, sum;

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i=0; i<n; ++i) scanf("%d", &a[i]);
		sort(a, a+n);
		for(int i=1; i<n; ++i)
		{
			sum ^= (a[i] - a[i-1]);
		}
		if(sum) puts("Georgia will win");
		else puts("Bob will win");
	}
	return 0;
}

