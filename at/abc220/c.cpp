#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

const int maxl = 1e5 + 10;
int n, a[maxl];
ll x, sum;

int main() {
    scanf("%d", &n);
    sum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    cin >> x;

    ll e = x / sum;
    x %= sum;
    ll ans = e * n;
    sum = 0;
    for (int i = 1; i <= n; i++) {
        ans++;
        sum += a[i];
        if (sum > x) {
            break;
        }
    }
    cout << ans << endl;

    return 0;
}

