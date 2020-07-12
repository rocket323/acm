#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;
#define ll long long

ll n, a, b, c;

bool Check(int k)
{
	if(n < (k - 1) * (b - c)) return false;
	ll x = n - (k - 1) * (b - c);
	if(x < b) return false;
	return true;
}

int main()
{
	while(cin >> n >> a >> b >> c)
	{
		if(a <= (b - c) || n < b)
		{
			ll ans = n / a;
			cout << ans << endl;
		}
		else
		{
			ll k = (n - b) / (b - c);
			k++;
			ll x = (n - k * (b - c)) / a;
			cout << k + x << endl;
		}
	}

	return 0;
}

