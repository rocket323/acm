#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

int t, n, nxt[maxl];
char s[maxl];

ll solve() {
    ll ans = 0;
    int i = 1;
    int cnt = 0;
    while (i <= n && s[i] == '#') {
        i++;
        cnt++;
    }

    for (; i <= n; ) {
        if (s[i] == '.') {
            i++;
            continue;
        }
        int j = i;
        while (j < n && s[j + 1] == '#') j++;

        if (j == i) {
            if (i == n)
                return -1;
            ans += (ll)(i - 1 - cnt);
        } else {
            int len = j - i;
            if (j + len + 1 <= n && nxt[j] > j + len + 1) {
                ans += (ll)(len + 1) * len / 2;
                int num = (j - i + 1);
                ans += (ll)(i - 1 - cnt) * num + (num - 1) * num / 2;
            } else {
                return -1;
            }
        }
        // printf("%d %d %lld\n", i, j, ans);
        cnt += (ll)(j - i + 1);
        i = j + 1;
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        scanf("%s", s + 1);

        nxt[n] = n + 1;
        for (int i = n - 1; i >= 1; i--) {
            if (s[i + 1] == '#')
                nxt[i] = i + 1;
            else
                nxt[i] = nxt[i + 1];
        }

        ll ans = solve();
        cout << ans << endl;
    }

    return 0;
}

