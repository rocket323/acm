#include <stdio.h>
#include <cmath>
#include <cstring>
#include <vector>
#include <set>
using namespace std;

const int maxl = 5 * 1e5 + 10;

vector<int> a[maxl];
int n, m, v;
char s[20];
multiset<int> s1;
set<int> s2;
multiset<int> b;

void del(int x) {
    s1.erase(s1.lower_bound(x));
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v);
        a[i].push_back(v);
        b.insert(v);
    }

    for (int i = 2; i <= n; i++) {
        int x = abs(a[i][0] - a[i - 1][0]);
        s1.insert(x);
    }

    int last = -1;
    for (int v : b) {
        if (last != -1) {
            s2.insert(v - last);
        }
        last = v;
    }

    for (int i = 0; i < m; i++) {
        scanf("%s", s);
        if (strcmp(s, "INSERT") == 0) {
            int x, y;
            scanf("%d%d", &x, &y);
            a[x].push_back(y);
            int l = a[x].size() - 1;

            s1.insert(abs(a[x][l] - a[x][l - 1]));
            if (x < n) {
                s1.insert(abs(a[x + 1][0] - a[x][l]));
                del(abs(a[x][l - 1] - a[x + 1][0]));
            }

            if (*s2.begin() == 0) {
                continue;
            }

            b.insert(y);
            auto iter = b.find(y);
            if (iter != b.begin()) {
                s2.insert(*iter - *(prev(iter)));
            }
            if (next(iter) != b.end()) {
                s2.insert(*(next(iter)) - *iter);
            }
        } else if (strcmp(s, "MIN_GAP") == 0) {
            printf("%d\n", *s1.begin());
        } else {
            printf("%d\n", *s2.begin());
        }
    }

    return 0;
}
