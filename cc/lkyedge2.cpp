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
const int maxl = 10010;
const int mod = 1e9 + 7;

struct edge {
    int u, v;
} e[maxl];

int t, m, n;
int p[maxl], sz[maxl];

struct dsu {
    int p[maxl];
    int rank[maxl];
    pair<int *, int> st[maxl];
    int top;
    int sp;
    int su, sv, fu, fv;

    inline void clear(int u, int v) {
        for (int i = 0; i <= n; ++i) {
            p[i] = i;
            rank[i] = 0;
        }
        top = 0;
        sp = -1;
        su = fu = u;
        sv = fv = v;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return find(p[x]);
    }
    inline bool connect(int u, int v) {
        int x, y;
        if (fu != -1) x = fu; else x = fu = find(u);

        if (fv != -1) y = fv;
        else y = fv = find(v);
        return x == y;
    }
    inline void add(int u, int v) {
        int x = find(u), y = find(v);
        if (x == y) return;

        if (rank[x] <= rank[y]) {
            st[++top] = make_pair(p + x, p[x]);
            p[x] = y;
            if (rank[x] == rank[y]) {
                st[++top] = make_pair(rank + y, rank[y]);
                ++rank[y];
            }
            if (fu == x) fu = y;
            if (fv == x) fv = y;
        } else {
            st[++top] = make_pair(p + y, p[y]);
            p[y] = x;

            if (fu == y) fu = x;
            if (fv == y) fv = x;
        }
    }
    inline void tag() {
        sp = top;
    }
    inline void restore() {
        if (sp < 0) return;
        while (top > sp) {
            *st[top].first = st[top].second;
            top--;
        }
        top = 0;
        sp = -1;
        fu = fv = -1;
    }

} d[80], dd;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &m);
        n = 1;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &e[i].u, &e[i].v);
            n = max(n, e[i].u);
            n = max(n, e[i].v);
        }

        int BS;
        if (m <= 1000) BS = sqrt(m) + 10;
        else BS = sqrt(m) * 30;
        for (int i = 0; i < m; ++i) {
            int u = e[i].u, v = e[i].v;
            int ans = 0;
            int buckets = i / BS + (i % BS > 0);

            for (int j = 0; j <= buckets; ++j)
                d[j].clear(u, v);
            for (int j = i - 1; j >= 0; --j) {
                int b = (i - j - 1) / BS + 1;
                for (int k = b; k < buckets; ++k)
                    d[k].add(e[j].u, e[j].v);
            }

            int pos = i;
            bool skip = false;
            for (int b = buckets - 1; b >= 0 && !skip; --b) {
                int right = i - 1 - b * BS;
                int left = right - BS + 1;
                if (left < 0) left = 0;

                for (int j = left; j <= right; ++j) {
                    d[b].tag();
                    
                    int old_pos = pos;
                    for (int k = j; k <= right; ++k)
                        d[b].add(e[k].u, e[k].v);

                    while (!d[b].connect(u, v) && pos + 1 < m) {
                        d[b].add(e[pos + 1].u, e[pos + 1].v);
                        pos++;
                    }
                    if (!d[b].connect(u, v)) {
                        skip = true;
                        break;
                    }
                    d[b].restore();

                    for (int k = old_pos + 1; k <= pos; ++k) {
                        for (int bb = 0; bb <= b; ++bb)
                            d[bb].add(e[k].u, e[k].v);
                    }
                    ans += (m - pos);
                }
            }

            while (!d[0].connect(u, v) && pos + 1 < m) {
                d[0].add(e[pos + 1].u, e[pos + 1].v);
                pos++;
            }
            if (d[0].connect(u, v)) ans += (m - pos);
            printf("%d%c", ans, (i == m - 1) ? '\n' : ' ');
        }
    }

    return 0;
}

