#include <stdio.h>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#define ll long long

ll a, b;
vector<ll> A[3], l, r, num;

ll pow(ll a, ll x, ll n)
{
	if(x == 0) return 1;
	ll mid = pow(a, x / 2, n);
	if(mid == 0) return 0;

	ll ans = (mid * mid) % n;
	if(ans == 1 && mid != 1 && mid != n - 1) return 0;

	if(x & 1) ans = (ans * a) % n;
	return ans;
}

bool isPrime(ll n)
{
	if(n == 1) return 0;
	if(n == 2) return 1;
	for(int i=0; i<5; ++i)
	{
		ll a = rand() % (n - 2) + 2;
		if(pow(a, n - 1, n) != 1) return 0;
	}
	return 1;
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
		x = (x * x - c) % n;
		ll d = gcd(y - x, n);
		if(d > 1 && d < n) return d;

		if(x == y) return n;

		if(i == k)
		{
			y = x;
			k <<= 1;
		}
	}
}

void factor(ll n, int idx)
{
	if(n == 1) return;
	if(isPrime(n)) A[idx].push_back(n);
	else
	{
		ll k = pollard_rho(n);
		factor(k, idx);
		factor(n / k, idx);
	}
}

void out(vector<ll> A)
{
	for(int i=0; i<A.size(); ++i) printf("%I64d ", A[i]);
	puts("");
}

ll find(vector<ll> A, ll x)
{
	ll ans = 0;
	for(int i=0; i<A.size(); ++i) if(A[i] == x) ans++;
	return ans;
}

ll pow2(ll a, ll n)
{
	ll ans = 1, t = a;
	while(n)
	{
		if(n & 1) ans *= t;
		t *= t;
		n >>= 1;
	}
	return ans;
}

void solve()
{
	l.clear(); r.clear(); num.clear();
	for(int i=0; i<A[0].size(); ++i)
	{
		if(i == 0 || A[0][i] != A[0][i-1])
		{
			num.push_back(A[0][i]);
			ll sum = find(A[0], num.back()) + find(A[1], num.back());
			ll dif = find(A[2], num.back());
			l.push_back((sum - dif) / 2);
			r.push_back((sum + dif) / 2);
		}
	}
	/*
	out(num);
	out(l);
	out(r);
	*/

	int n = num.size();
	ll ans = 1e17, ra = -1, rb = -1;

	for(int i=0; i<n; ++i) l[i] = pow2(num[i], l[i]), r[i] = pow2(num[i], r[i]);

	for(int i=0; i<(1<<n); ++i)
	{
		ll a = 1, b = 1;
		for(int j=0; j<n; ++j)
		{
			if(i & (1<<j)){ a *= l[j]; b *= r[j]; }
			else{ b *= l[j]; a *= r[j]; }
		}

		//printf("n %d %I64d %I64d\n", i, a, b);

		if(a + b < ans)
		{
			ans = a + b;
			ra = a; rb = b;
		}
	}

	if(ra > rb) printf("%I64d %I64d\n", rb, ra);
	else printf("%I64d %I64d\n", ra, rb);
}

int main()
{
	while(scanf("%I64d%I64d", &a, &b) != EOF)
	{
		for(int i=0; i<3; ++i) A[i].clear();
		factor(b, 0);
		factor(a, 1);
		factor(b / a, 2);
		for(int i=0; i<3; ++i) sort(A[i].begin(), A[i].end());

		//for(int i=0; i<3; ++i) out(A[i]);

		solve();
	}
	return 0;
}

