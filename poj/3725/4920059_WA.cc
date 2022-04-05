#include <iostream>
#include <algorithm>
#include <sstream>
#define ll long long
using namespace std;

ll n, m, k, flag;
ll bit;
ll num[19];
ll p[19];

void init()
{
	bit = 0;
	ll tmp = m;
	while(tmp){ bit++; tmp /= 10; }
	
	num[0] = 0;
	for(ll i=1; i<18; ++i) num[i] = (ll)num[i-1] * 10 + 9;
	p[0] = 1;
	for(ll i=1; i<18; ++i) p[i] = (ll)p[i-1] * 10;
}

ll go(ll w, ll last)
{
	ll left = k-1 - last;
	ll ans = p[w-1];
	if(w==1) ans++;
	ans += (left - 1);
	
	if(ans==m-1) return m;
	
	if(ans < m) return 0;
	else return ans;
}

void solve()
{
	flag = 0;
	ll cnt = 0, last = 0;
	ll i;
	for(i=1; i<=18; ++i)
	{
		last = cnt;
		if(i < bit)
		{
			ll tmp = m, add = 0;
			for(ll j=1; j<=(bit-i); ++j) tmp /= 10;
			cnt += tmp;
		}
		else
		{
			cnt += ( (ll)(m - p[bit-1]) * p[i-bit] );
		}
		if(cnt >= k-1)
		{
			int x = go(i, last);
			if(x > 0){ cout<<x<<endl; return; }
		}
	}
	printf("0\n");
}

int main()
{
	while(cin>>k>>m)
	{
		init();
		solve();
	}
	return 0;
}
