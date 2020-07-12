#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxl 30
#define ll long long

int n, a[maxl];

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", &a[i]);
		}

		sort(a, a + n, greater<int>());

		ll ans = 0;
		for(int i = 0; i < n; ++i)
		{
			if(i > 0 && a[i] >= a[i-1] && a[i] > 0) a[i] = a[i-1] - 1;
			if(a[i] > 0)
				ans = ans + a[i];
		}
		cout << ans << endl;
	}

	return 0;
}

