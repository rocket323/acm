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

int t, n, s[maxl];
int x, y;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &x);
        scanf("%d", &n);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &s[i]);
        }
        scanf("%d", &y);
        ans = y - x + 1;
        for (int i = 0; i < n; i++) {
            if (s[i] < y)
                ans--;
        }
        printf("%d\n", ans);
    }
    return 0;
}
