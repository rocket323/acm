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

int t, n;
char s[maxl];

void solve() {
    int l = -1, r = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] < s[i - 1]) {
            l = i - 1;
            r = i;
            break;
        }
    }
    if (l >= 0) {
        for (int i = r + 1; i <= n; i++) {
            if (s[i] > s[l] || i == n) {
                r = i - 1;
                break;
            }
        }
    } else {
        l = r = 0;
    }
    for (int i = 0; i < l; i++) {
        printf("%c", s[i]);
    }
    for (int i = l + 1; i <= r; i++) {
        printf("%c", s[i]);
    }
    printf("%c", s[l]);
    for (int i = r + 1; i < n; i++) {
        printf("%c", s[i]);
    }
    printf("\n");
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        scanf("%s", s);
        solve();
    }
    return 0;
}