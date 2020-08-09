#include <stdio.h>
#include <cstring>
#define ll long long
#include <iostream>
using namespace std;

ll l, r, k;
ll a[100], top;

int main()
{
	while(cin >> l >> r >> k)
	{
		ll x = 1;
		top = 0;
		while(x <= r)
		{
			if(x >= l) a[top++] = x;
			if(x > r / k) break;
			x *= k;
		}
		if(top == 0) { puts("-1"); continue; }
		for(int i=0; i<top; ++i)
		{
			cout << a[i];
			if(i == top - 1) cout << '\n';
			else cout << ' ';
		}
	}

	return 0;
}

