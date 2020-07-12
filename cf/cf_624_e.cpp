#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <stdlib.h>
using namespace std;
#define maxl 200010
#define ll long long
#define INF 1e17
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

ll n;
ll min_l_y[maxl], max_l_y[maxl], min_r_y[maxl], max_r_y[maxl];

struct Point
{
	ll x, y;
} p[maxl];

bool cmp(const Point& a, const Point& b)
{
	return a.x < b.x;
}

ll square(ll n)
{
	return (ll)n * n;
}

bool Check(ll m)
{
	ll min_y = INF, max_y = -INF;

	if(square(max_l_y[n] - min_l_y[n]) <= m) return true;
	if(square(p[n].x - p[1].x) <= m) return true;

	ll last = 1;
	for(ll i = 1; i <= n; ++i)
	{
		if(p[i].x > 0) break;
		while(last > i && abs(p[last].x) > abs(p[i].x)) last--;
		while(last + 1 <= n && abs(p[last+1].x) <= abs(p[i].x) && square(p[last+1].x - p[i].x) <= m) last++;
		assert(last >= i);
		min_y = min(min_l_y[i-1], min_r_y[last+1]);
		max_y = max(max_l_y[i-1], max_r_y[last+1]);

		bool check1 = (min_y != INF && square(max_y - min_y) <= m);
		bool check2 = (min_y != INF && square(p[i].x) + square(min_y) <= m);
		bool check3 = (max_y != -INF && square(p[i].x) + square(max_y) <= m);

		if(check1 && check2 && check3) return true;
	}

	last = n;
	for(ll i = n; i >= 1; --i)
	{
		if(p[i].x < 0) break;
		while(last < i && abs(p[last].x) > abs(p[i].x)) last++;
		while(last - 1 >= 1 && (abs(p[last-1].x) <= abs(p[i].x)) && square(p[last-1].x - p[i].x) <= m) last--;
		assert(abs(p[last].x) <= abs(p[i].x));
		min_y = min(min_r_y[i+1], min_l_y[last-1]);
		max_y = max(max_r_y[i+1], max_l_y[last-1]);

		bool check1 = (min_y != INF && square(max_y - min_y) <= m);
		bool check2 = (min_y != INF && square(p[i].x) + square(min_y) <= m);
		bool check3 = (max_y != -INF && square(p[i].x) + square(max_y) <= m);
	
		if(check1 && check2 && check3) return true;
	}

	return false;
}

int main()
{
	cin >> n;
	{
		for(ll i = 1; i <= n; ++i)
		{
			cin >> p[i].x >> p[i].y;
		}
		sort(p + 1, p + 1 + n, cmp);

		min_l_y[0] = INF, max_l_y[0] = -INF;
		for(ll i = 1; i <= n; ++i)
		{
			min_l_y[i] = min(min_l_y[i-1], p[i].y);
			max_l_y[i] = max(max_l_y[i-1], p[i].y);
		}

		min_r_y[n+1] = INF, max_r_y[n+1] = -INF;
		for(ll i = n; i >= 1; --i)
		{
			min_r_y[i] = min(min_r_y[i+1], p[i].y);
			max_r_y[i] = max(max_r_y[i+1], p[i].y);
		}

		ll l = 0, r = INF, ans = INF;
		while(l <= r)
		{
			ll mid = (l + r) / 2;
			bool check = Check(mid);
			if(check)
			{
				ans = mid;
				r = mid - 1;
			}
			else
				l = mid + 1;
		}
		cout << ans << endl;
	}

	return 0;
}

