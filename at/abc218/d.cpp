#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int maxl = 2010;
vector<int> r[maxl];
int n, x[maxl], y[maxl], b[maxl], top;

int gao(vector<int> &a, vector<int> &b) {
    int p1 = 0, p2 = 0, cnt = 0;
    while (p1 < a.size() && p2 < b.size()) {
        if (a[p1] == b[p2]) {
            cnt++;
            p1++;
            p2++;
        } else if (a[p1] < b[p2]) {
            p1++;
        } else {
            p2++;
        }
    }

    return cnt * (cnt - 1) / 2;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        top = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &x[i], &y[i]);
            b[top++] = x[i];
        }
        sort(b, b + top);
        top = unique(b, b + top) - b;
        for (int i = 0; i < top; i++)
            r[i].clear();

        for (int i = 0; i < n; i++) {
            int row = lower_bound(b, b + top, x[i]) - b;
            r[row].push_back(y[i]);
        }
        for (int i = 0; i < top; i++) {
            sort(r[i].begin(), r[i].end());
        }

        int ans = 0;
        for (int i = 0; i < top; i++) {
            for (int j = i + 1; j < top; j++) {
                ans += gao(r[i], r[j]);
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}

