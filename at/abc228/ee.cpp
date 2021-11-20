#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;

ll maxi = 998244353;
ll powe(ll a, ll b, ll m){
	ll res = 1;
	while(b){
		if(b%2 != 0){
			res = ((res%m)*(a%m))%m;
		}
		a = ((a%m)*(a%m))%m;
		b/=2;
	}
	return res%m;
}
int main() {
    ll n, k, m;
    cin>>n>>k>>m;
    ll temp = powe(k, n, maxi-1);
    ll ans = powe(m, temp, maxi);
    if(m%maxi == 0) ans = 0;
    cout<<ans%maxi<<endl;
    return 0;
}
