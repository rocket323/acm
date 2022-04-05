#include <iostream>
#include <algorithm>
#include <sstream>
#define ll long long
using namespace std;

ll n, m, k, flag;
ll bit;
ll num[10];
ll p[10];

void init()
{
	bit = 0;
	ll tmp = m;
	while(tmp){ bit++; tmp /= 10; }
	
	num[0] = 0;
	for(ll i=1; i<10; ++i) num[i] = (ll)num[i-1] * 10 + 9;
	p[0] = 1;
	for(ll i=1; i<10; ++i) p[i] = (ll)p[i-1] * 10;
}

void go(ll w, ll last)
{
	ll left = k-1 - last;
	ll ans = p[w-1];
	if(w==1) ans++;
	//cout<<w<<' '<<last<<' '<<ans<<' '<<left<<endl;
	ans += (left - 1);
	if(ans < m) printf("0\n");
	else printf("%d\n", ans);
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
			//cout<<last<<' '<<cnt<<' '<<cnt-last<<endl;
		}
		else
		{
			cnt += ( (ll)(m - p[bit-1]) * p[i-bit] );
			//cout<<last<<' '<<cnt<<' '<<cnt-last<<endl;
		}
		if(cnt >= k-1){ flag = 1; break; }
	}
	if(!flag) printf("0\n");
	else
	{
		go(i, last);
	}
}

int main()
{
	while(scanf("%d%d", &k, &m)!=EOF)
	{
		init();
		solve();
	}
	return 0;
}
