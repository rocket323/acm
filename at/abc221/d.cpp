#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

using ll = long long;
const int maxl = 5e5 + 10;

int n, a[maxl], b[maxl];
map<int, int> mp;
ll ans[maxl];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a[i], &b[i]);
        mp[a[i]]++;
        mp[a[i] + b[i]]--;
    }

    int lp = 0, cnt = 0;
    for (auto &kv : mp) {
        int p = kv.first;
        int inc = kv.second;
        ans[cnt] += (p - lp);
        lp = p;
        cnt += inc;
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i];
        if (i == n)
            cout << endl;
        else
            cout << ' ';
    }

    return 0;
}

