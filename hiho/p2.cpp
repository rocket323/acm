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

int t, n, a[maxl];
int r[maxl];
ll f[maxl][26];
ll s[26];

void add(ll &a, ll b) {
    a += b;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            r[a[i]] = i;
        }

        ll ans = 0;
        memset(f, 0, sizeof f);
        for (int i = 0; i < 26; ++i)
            f[1][i] = 1;

        for (int i = 2; i <= n; ++i) {
            s[0] = f[i - 1][0];
            for (int j = 1; j < 26; ++j)
                s[j] = s[j - 1] + f[i - 1][j];

            for (int j = 0; j < 26; ++j) {
                if (j > 0)
                    f[i][j] = s[j - 1];

                if (r[a[i - 1] + 1] < r[a[i] + 1])
                    f[i][j] += f[i - 1][j];
            }
        }

        for (int i = 0; i < 26; ++i)
            add(ans, f[n][i]);
        
        cout << ans << endl;
    }

    return 0;
}

