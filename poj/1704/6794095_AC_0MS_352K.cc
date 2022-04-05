#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

int a[1010], n, sum;
int list[1010], top;

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i=0; i<n; ++i) scanf("%d", &a[i]);
		a[n++] = 0;
		sort(a, a+n);

		top = 0;

		for(int i=1; i<n; ++i) list[i] = a[i] - a[i-1] - 1;

		sum = 0;
		for(int i=n-1; i>=1; i-=2) sum ^= list[i];

		if(sum) puts("Georgia will win");
		else puts("Bob will win");
	}
	return 0;
}

