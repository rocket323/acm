#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int q, n, t[maxl], a[maxl];

int main() {
    scanf("%d", &q);
    while (q--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &t[i]);
        }

        a[0] = 1;
        int cnt = 1;
        for (int i = 1; i < n; i++) {
            a[i] = a[i - 1];
            if (t[i] != t[i - 1]) {
                cnt = 2;
                a[i] = 3 - a[i - 1];
            }
        }
        if (n > 1 && t[n - 1] != t[0] && a[n - 1] == a[0]) {
            int pos = -1;
            for (int i = 1; i < n; i++) {
                if (t[i] == t[i - 1]) {
                    pos = i;
                    break;
                }
            }
            if (pos != -1) {
                for (int i = pos; i < n; i++) {
                    a[i] = 3 - a[i];
                }
            } else {
                cnt = 3;
                a[n - 1] = 3;
            }
        }
        printf("%d\n", cnt);
        for (int i = 0; i < n; i++) {
            printf("%d%c", a[i], i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
