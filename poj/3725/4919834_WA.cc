#include <iostream>
#include <algorithm>
#include <sstream>
#define ll long long
using namespace std;

ll n, m, k, flag;
ll bit;
ll num[16];
ll p[16];

void init()
{
	bit = 0;
	ll tmp = m;
	while(tmp){ bit++; tmp /= 10; }
	
	num[0] = 0;
	for(ll i=1; i<16; ++i) num[i] = (ll)num[i-1] * 10 + 9;
	p[0] = 1;
	for(ll i=1; i<16; ++i) p[i] = (ll)p[i-1] * 10;
}

int go(ll w, ll last)
{
	ll left = k-1 - last;
	ll ans = p[w-1];
	//cout<<w<<' '<<left<<' '<<ans<<endl;
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
	for(i=1; i<=8; ++i)
	{
		last = cnt;
		if(i < bit)
		{
			ll tmp = m, add = 0;
			for(ll j=1; j<=(bit-i); ++j) tmp /= 10;
			cnt += tmp;
			//cout<<"h1 "<<i<<' '<<last<<' '<<cnt<<' '<<cnt-last<<endl;
		}
		else
		{
			cnt += ( (ll)(m - p[bit-1]) * p[i-bit] );
			//cout<<"h2 "<<i<<' '<<last<<' '<<cnt<<' '<<cnt-last<<endl;
		}
		if(cnt >= k-1)
		{
			int x = go(i, last);
			//cout<<i<<' '<<x<<endl;
			if(x > 0){ printf("%I64d\n", x); return; }
		}
	}
	printf("0\n");
}

int main()
{
	while(scanf("%I64d%I64d", &k, &m)!=EOF)
	{
		init();
		solve();
	}
	return 0;
}
