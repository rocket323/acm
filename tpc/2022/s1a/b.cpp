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
const int maxl = 4e6 + 10;

int t;
int n, r[maxl], s[maxl];

int check(int u) {
    int req = r[0] - u;
    for (int i = 1; i < n; i++) {
        if (req > s[i])
            return -1;
        if (s[i] >= req + r[i])
            req = 0;
        else
            req = req + r[i] - s[i];
    }
    return req;
}

bool check2(int u) {
    int x = check(u);
    if (x == -1)
        return false;

    return u + x <= s[0];
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &r[i]);
        for (int i = 0; i < n; i++)
            scanf("%d", &s[i]);

        int left = 0, right = min(r[0], s[0]);
        int use = -1;
        while (left <= right) {
            int mid = (left + right) / 2;
            int x = check(mid);
            // printf("%d %d %d %d\n", left, right, mid, x);
            if (x >= 0) {
                right = mid - 1;
                use = mid;
            } else {
                left = mid + 1;
            }
        }

        puts(check2(use) ? "Yes" : "No");
    }
    return 0;
}