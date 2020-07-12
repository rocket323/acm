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
const int maxl = 1000010;
const int mod = 1e9 + 7;

int t, n;
vector<vector<int>> a;
pair<int, ll> st1[maxl], st2[maxl];
int top1, top2;
map<int, ll, greater<int>> f1;
map<int, ll> f2;

template<typename T>
void addf(T &f, int y, ll val) {
    auto iter = f.find(y);
    if (iter == f.end()) {
        f.insert(make_pair(y, val));
    } else {
        ll old = iter->second;
        if (val > old)
            f[y] = val;
    }
}

template<typename T>
void addst(pair<int, ll> st[], int &top, T &f) {
    top = 0;
    for (auto iter = f.begin(); iter != f.end(); ++iter) {
        if (top > 0 && st[top - 1].second >= iter->second)
            continue;
        st[top++] = *iter;
    }
}

void out(const char *name, pair<int, ll> st[], int top) {
    for (int i = 0; i < top; ++i)
        printf("%s %d %lld\n", name, st[i].first, st[i].second);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        a.resize(n);
        int m, x;
        for (int i = 0; i < n; ++i) {
            a.clear();
            scanf("%d", &m);
            for (int j = 0; j < m; ++j) {
                scanf("%d", &x);
                a[i].push_back(x);
            }
        }

        f1.clear();
        f2.clear();
        for (int i = 0; i < a[0].size(); ++i) {
            int y = a[0][i];
            addf(f1, y, 0 + 1 * y);
            addf(f2, y, 0 - 1 * y);
        }
        addst(st1, top1, f1);
        addst(st2, top2, f2);

        ll ans = 0;
        for (int i = 1; i < n; ++i) {
            f1.clear();
            f2.clear();
            // printf("xx %d\n", i);
            // out("st1", st1, top1);
            // out("st2", st2, top2);
            for (int j = 0; j < a[i].size(); ++j) {
                int x = a[i][j], y = a[i][(j + a[i].size() - 1) % a[i].size()];
                ll v1 = -1, v2 = -1;

                int l = 0, r = top1 - 1;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    if (st1[mid].first >= x) {
                        l = mid + 1;
                        v1 = st1[mid].second - (ll)x * i;
                    } else {
                        r = mid - 1;
                    }
                }

                l = 0, r = top2 - 1;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    if (st2[mid].first <= x) {
                        l = mid + 1;
                        v2 = st2[mid].second + (ll)x * i;
                    } else {
                        r = mid - 1;
                    }
                }

                ll v = max(v1, v2);
                ans = max(ans, v);
                addf(f1, y, v + (ll)(i + 1) * y);
                addf(f2, y, v - (ll)(i + 1) * y);
            }

            addst(st1, top1, f1);
            addst(st2, top2, f2);
        }
        printf("%lld\n", ans);
    }

    return 0;
}

