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

int t, n, q, m;
vector<vector<int>> small;
vector<vector<int>> s;
int total[maxl];
int bv1[maxl];
int bv2[maxl];
int big[maxl * 2];
int sbig[maxl * 2];

int qsmall(int c, int v1, int v2) {
    if (v1 == v2) return 0;
    if (v1 > v2) swap(v1, v2);

    int l = s[c][v1] - s[c][v2];
    return min(l, total[c] - l);
}

int qbig(int c1, int c2) {
    if (c1 == c2) return 0;
    if (c2 < c1) c2 += n;

    int l = sbig[c2] - sbig[c1];
    return l - qsmall(c2 % n, bv1[c2 % n], bv2[c2 % n]);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &q);
        small.resize(n);
        s.resize(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &m);
            small[i].resize(m);
            s[i].resize(m);
            total[i] = 0;
            for (int j = 0; j < m; ++j) {
                int v;
                scanf("%d", &v);
                small[i][j] = v;
                total[i] += small[i][j];
            }
            s[i][m - 1] = 0;
            for (int j = m - 2; j >= 0; --j)
                s[i][j] = s[i][j + 1] + small[i][j];
        }

        int u, v, w;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            bv1[i] = u - 1;
            bv2[(i + 1) % n] = v - 1;
            big[i] = w;
            big[i + n] = w;
        }
        sbig[0] = 0;
        for (int i = 1; i < 2 * n; ++i) {
            int c = i % n;
            int l = big[i - 1] + qsmall(c, bv1[c], bv2[c]);
            sbig[i] = sbig[i - 1] + l;
            // printf("%d %d %d %d\n", i, sbig[i], big[i - 1], qsmall(c, bv1[c], bv2[c]));
        }

        for (int i = 0; i < q; ++i) {
            int v1, c1, v2, c2;
            scanf("%d%d%d%d", &v1, &c1, &v2, &c2);
            v1--; c1--;
            v2--; c2--;

            assert(c1 != c2);
            int l1 = qsmall(c1, v1, bv1[c1]) + qbig(c1, c2) + qsmall(c2, bv2[c2], v2);
            int l2 = qsmall(c2, v2, bv1[c2]) + qbig(c2, c1) + qsmall(c1, bv2[c1], v1);

            // printf("%d %d %d\n", qsmall(c2, v2, bv1[c2]), qbig(c2, c1), qsmall(c1, bv2[c1], v1));
            int ans = min(l1, l2);
            printf("%d\n", ans);
        }
    }

    return 0;
}

