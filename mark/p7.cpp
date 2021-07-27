#include <bits/stdc++.h>
using namespace std;

const int maxl = 1e5 + 10;
int n, a[maxl], t;
unordered_map<int, int> mp;

void add(int x) {
    mp[x]++;
}

void dec(int x) {
    mp[x]--;
    if (mp[x] == 0)
        mp.erase(x);
}

bool check(int x) {
    for (auto &kv : mp) {
        int y = kv.first;
        if (x % y != 0 && y % x != 0)
            return false;
    }
    return true;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            // printf("%d ", a[i]);
        }
        // puts("");
        mp.clear();

        int l = 1, r = l, ans = 1;
        add(a[l]);
        while (l <= n) {
            while (r + 1 <= n && check(a[r + 1])) {
                r++;
                add(a[r]);
            }
            // printf("%d %d\n", l, r);
            ans = max(ans, r - l + 1);

            dec(a[l]);
            l++;
            if (r < l) {
                add(a[l]);
                r = l;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
