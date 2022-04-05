#include <iostream>
#include <algorithm>
#include <sstream>
#define ll long long
using namespace std;

ll n, m, k, flag;
ll bit;
ll num[20];
ll p[20];

void init()
{
	bit = 0;
	ll tmp = m;
	while(tmp){ bit++; tmp /= 10; }
	
	num[0] = 0;
	for(ll i=1; i<20; ++i) num[i] = (ll)num[i-1] * 10 + 9;
	p[0] = 1;
	for(ll i=1; i<20; ++i) p[i] = (ll)p[i-1] * 10;
}

ll go(ll w, ll last)
{
	ll left = k-1 - last;
	ll ans = p[w-1];
	
	ans += (left - 1);
	
	if(left < 0){  return 0;}
	if(ans==m-1) return m;
	
	if(ans < m){ return 0;}
	return ans;
}

ll dp(ll num, int pos, int bit)
{

	if(num==0) return 1;

	ll k;
	ll head = num / p[bit];
	if(pos==1) k = head -1;
	else k = head;
	
	return (ll)k * p[bit] + dp(num%p[bit], pos+1, bit-1);
}

void solve()
{
	flag = 0;
	ll cnt = 0, last = 0;
	ll i;
	
	for(i=1; i<20; ++i)
	{
		last = cnt;
		if(i < bit)
		{
			ll tmp = m, mod = 1;   
			for(ll j=1; j<=(bit-i); ++j) tmp /= 10;
			cnt += dp(tmp, 1, i-1);
		}
		else
		{
			cnt += ( (ll)(m - p[bit-1]) * p[i-bit] );
		}
		
		if(cnt >= k-1)
		{
			ll x = go(i, last);
			if(x > 0){ cout<<x<<endl; return; }
		}
	}
	printf("0\n");
}

int main()
{
	while(scanf("%I64d%I64d", &m, &k)!=EOF)
	{
		init();
		solve();
	}
	return 0;
}
