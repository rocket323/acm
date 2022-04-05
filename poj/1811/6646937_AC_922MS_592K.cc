#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stdlib.h>
using namespace std;
#define ll long long

vector<ll> factor;

ll multiply(ll a, ll n, ll mod)
{
	ll ans = 0, t = a % mod;
	while(n)
	{
		if(n & 1) ans = (ans + t) % mod;
		t = (t + t) % mod;
		n /= 2;
	}
	return ans;
}

ll pow(ll a, ll x, ll n)
{
	if(x == 0) return 1;
	ll mid = pow(a, x / 2, n);
	if(mid == 0) return 0;

	ll y = multiply(mid, mid, n);
	if(y == 1 && mid != 1 && mid != n - 1) return 0;

	if(x & 1) y = multiply(y, a, n);
	return y;
}

bool isPrime(ll n)
{
	if(n == 1) return false;
	if(n == 2) return true;

	for(ll i=0; i<5; ++i)
	{
		ll a = rand() % (n - 2) + 2;
		if(pow(a, n - 1, n) != 1) return false;
	}
	return true;
}

ll gcd(ll a, ll b)
{
	if(b == 0) return a;
	else return gcd(b, a % b);
}

ll pollard_rho(ll n)
{
	ll i = 1, x = rand() % (n - 1) + 1, y = x, k = 2, d;
	ll c = rand() % (n - 1) + 1;

	while(true)
	{
		i++;
		x = (multiply(x, x, n) - c) % n;
		d = gcd(y - x, n);
		if(d > 1 && d < n) return d;
		if(y == x) return n;

		if(i == k)
		{
			y = x;
			k <<= 1;
		}
	}
}

void solve(ll n)
{
	if(n == 1) return;
	if(isPrime(n)) factor.push_back(n);
	else
	{
		ll k = pollard_rho(n);
		solve(k);
		solve(n / k);
	}
}

int main()
{
	ll n, m, t;

	scanf("%I64d", &t);
	while(t--)
	{
		scanf("%I64d", &n);
		if(isPrime(n)) puts("Prime");
		else
		{
			factor.clear();
			solve(n);
			sort(factor.begin(), factor.end());
			printf("%I64d\n", factor[0]);
		}
	}
	return 0;
}

