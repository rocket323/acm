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
const int maxl = 1e5 + 10;

int t, n, k;
vector<int> ans;
int a[60];

void gao(int n, int k) {
    if (k % 2 == 0) {
        if (k == 0) {
            puts("YES");
            puts("0");
        } else {
            puts("NO");
        }
        return;
    }

    memset(a, 0, sizeof a);
    int kk = k, cnt = 0;
    for (int i = 0; i < 32; i++) {
        ll x = (1LL) << i;
        ll y = (1LL) << (i + 1);
        if (x > k) {
            break;
        }
        cnt = i;
        if (y & k || y > k) {
            a[i] = -1;
            k -= x;
        } else {
            a[i] = 1;
            k += x;
        }
    }

    k = kk;
    int last = -1;
    for (int i = 0; i <= cnt; i++) {
        if (a[i] == 1)
            continue;

        ll len = (1LL) << i;
        int pos = k - len + 1;
        int p = pos;
        for (int j = last + 1; j < i; j++) {
            ans.push_back(p);
            p += ((1LL) << j);
            k += ((1LL) << j);
        }
        ans.push_back(pos);
        k -= len;
        last = i;
    }

    puts("YES");
    printf("%zu\n", ans.size());
    for (int x : ans) {
        printf("%d\n", x);
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        ans.clear();
        scanf("%d%d", &n, &k);
        gao(n, k);
    }
    return 0;
}

