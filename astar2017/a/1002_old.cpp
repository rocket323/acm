#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define maxl 200010
using namespace std;

int b[maxl], top, p[maxl];
int x[maxl], y[maxl], e[maxl];
set<int> st[maxl];
set<int>::iterator it1, it2;
int last;
vector<int> ans;
vector<int> cls;
set<int> cls2;
int l;

int find(int x) {
    if (p[x] == x) return x;
    return p[x] = find(p[x]);
}

void Record(int i) {
    ans.push_back(i - last);
    last = i;

    for (int i = 0; i < cls.size(); ++i)
        p[cls[i]] = cls[i];
    cls.clear();

    for (it1 = cls2.begin(); it1 != cls2.end(); ++it1) {
        st[*it1].clear();
    }
    cls2.clear();
}

int main() {
    scanf("%d", &l);
    top = 0;
    for (int i = 0; i < l; ++i) {
        scanf("%d%d%d", &x[i], &y[i], &e[i]);
        if (x[i] > y[i]) swap(x[i], y[i]);
        b[top++] = x[i];
        b[top++] = y[i];
    }
    sort(b, b + top);
    top = unique(b, b + top) - b;

    for (int i = 0; i <= top; ++i) p[i] = i;
    last = -1;
    for (int i = 0; i < l; ++i) {
        int x1 = lower_bound(b, b + top, x[i]) - b;
        int y1 = lower_bound(b, b + top, y[i]) - b;

        int dx = find(x1);
        int dy = find(y1);

        if (e[i] == 0) {
            if (dx == dy) {
                Record(i);
            } else {
                st[dx].insert(dy);
                st[dy].insert(dx);

                cls2.insert(dx);
                cls2.insert(dy);
            }
        } else {
            if (x1 == y1) continue;
            if (st[dx].find(dy) != st[dx].end() ||
                    st[dy].find(dx) != st[dy].end()) {
                Record(i);
            } else {
                if (dx == dy) continue;
                if (st[dx].size() >= st[dy].size())
                    swap(dx, dy);

                p[dx] = dy;
                cls.push_back(dx);
                for (it1 = st[dx].begin(); it1 != st[dx].end(); ++it1) {
                    st[dy].insert(*it1);
                    st[*it1].insert(dy);
                }
            }
        }
    }
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); ++i)
        printf("%d\n", ans[i]);

    return 0;
}

