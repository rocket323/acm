#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define ll long long

ll a, b;

int main()
{
	while(cin >> a >> b)
	{
		ll now = 2;
		int cnt = 1;

		int ans = 0;
		while(now <= b)
		{
			now <<= 1;
			cnt++;
			ll mask = now - 1;

			for(int i=0; i<cnt-1; ++i)
			{
				ll num = mask ^ (1LL << i);
				if(num >= a && num <= b) ans++;
			}
		}
		printf("%d\n", ans);
	}

	return 0;
}

