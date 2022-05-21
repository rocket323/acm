#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int n, a[maxl];
ll m;
priority_queue<ll, vector<ll>, greater<ll>> q;

int main() {
    cin >> n >> m;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sum = sum + a[i];
        q.push(a[i]);
    }
    if (m > sum) {
        q.push(m - sum);
        n++;
    }
    ll ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ll x = q.top();
        q.pop();
        ll y = q.top();
        q.pop();
        ans += x + y;
        q.push(x + y);
    }
    cout << ans << endl;
    return 0;
}