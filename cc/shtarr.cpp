#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 1000010;
const int mod = 1e9 + 7;

int t, n, q, h[maxl];
vector<vector<int>> v;
int BS, cnt;

void build(int block) {
    int start = block * BS;
    int end = min(n, start + BS);

    auto &st = v[block];
    st.clear();
    for (int i = start; i < end; ++i) {
        if (st.empty() || st.back() < h[i])
            st.push_back(h[i]);
    }
}

int query(int block, int x, int l, int r) {
    int ans = 0, mx = 0;
    int start = block * BS;
    int end = min(n, start + BS);

    for (int i = start; i < end; ++i) {
        if (i >= x) {
            if (h[i] <= mx) continue;

            if (h[i] >= l && mx < r) {
                ans++;
            }
            mx = h[i];
        }
    }
    
    for (int b = block + 1; b < cnt; ++b) {
        if (mx >= r) break;
        auto &st = v[b];

        auto left = upper_bound(st.begin(), st.end(), mx);
        if (mx < l)
            left = lower_bound(st.begin(), st.end(), l);

        auto right = lower_bound(st.begin(), st.end(), r);

        int cnt = 0;
        if (left != st.end()) {
            if (right == st.end())
                cnt = st.end() - left;
            else
                cnt = right - left + 1;
        }
        ans += cnt;
        mx = max(mx, st.back());
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &q);
        BS = sqrt(1e6) + 10;
        cnt = n / BS + (n % BS > 0);
        v.resize(cnt);

        for (int i = 0; i < n; ++i)
            scanf("%d", &h[i]);
        for (int i = 0; i < cnt; ++i)
            build(i);

        char s[100] = {0};
        for (int i = 0; i < q; ++i) {
            scanf("%s", s);
            if (s[0] == '+') {
                int a, x;
                scanf("%d%d", &a, &x);
                a--;
                h[a] += x;
                build(a / BS);
            } else {
                int x, l, r;
                scanf("%d%d%d", &x, &l, &r);
                x--;
                int ans = 0;
                int block = x / BS;
                ans = query(block, x, l, r);
                printf("%d\n", ans);
            }
        }
    }

    return 0;
}

