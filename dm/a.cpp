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
const int maxl = 1e7 + 10;

int f[maxl], n, t, nxt[maxl];
set<int> s;

int gao(int n) {
    while (n) {
        if (n % 10 == 7)
            return 1;
        n /= 10;
    }
    return 0;
}

int main() {
    f[7] = 1;
    for (int i = 1; i < maxl; i++) {
        int g = gao(i);
        f[i] |= g;
        if (f[i] == 1) {
            for (int j = i + i; j < maxl; j += i) {
                f[j] = 1;
            }
        }
    }

    nxt[maxl - 1] = -1;
    int ans = 0;
    for (int i = maxl - 2; i >= 1; i--) {
        if (f[i + 1])
            nxt[i] = nxt[i + 1];
        else {
            nxt[i] = i + 1;
            ans++;
        }
    }
    // cout << ans << endl;

    // puts("11");
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        if (f[n])
            puts("-1");
        else
            printf("%d\n", nxt[n]);
    }

    return 0;
}
