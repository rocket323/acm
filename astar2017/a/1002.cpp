#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define maxl 200010
using namespace std;

int p[maxl];
int x[maxl], y[maxl], e[maxl];
set<int> st[maxl];
set<int>::iterator it1, it2;
vector<int> ans;
set<int> cls;
int l, sum;

int find(int x) {
    if (p[x] == x) return x;
    return p[x] = find(p[x]);
}

void Record() {
    ans.push_back(sum);
    sum = 0;

    for (it1 = cls.begin(); it1 != cls.end(); ++it1) {
        p[*it1] = *it1;
        st[*it1].clear();
    }
    cls.clear();
}

int main() {
    scanf("%d", &l);
    for (int i = 0; i < l; ++i) {
        scanf("%d%d%d", &x[i], &y[i], &e[i]);
    }

    for (int i = 0; i < maxl; ++i) {
        p[i] = i;
    }

    sum = 0;
    for (int i = 0; i < l; ++i) {
        sum++;
        int x1 = x[i];
        int y1 = y[i];

        cls.insert(x1);
        cls.insert(y1);

        int dx = find(x1);
        int dy = find(y1);

        if (e[i] == 1) {
            if (dx == dy || st[dx].count(dy) == 0) {
                if (st[dx].size() >= st[dy].size())
                    swap(dx, dy);

                p[dx] = dy;
                cls.insert(dx);
                for (it1 = st[dx].begin(); it1 != st[dx].end(); ++it1) {
                    st[dy].insert(*it1);
                    st[*it1].insert(dy);
                    st[*it1].erase(*it1);
                }
            } else {
                Record();
            }
        } else {
            if (dx == dy) {
                Record();
            } else {
                st[dx].insert(dy);
                st[dy].insert(dx);
            }
        }
    }
    printf("%zu\n", ans.size());
    for (int i = 0; i < ans.size(); ++i)
        printf("%d\n", ans[i]);

    return 0;
}

