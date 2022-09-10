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

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

struct node {
    int p, y;
    int idx, rank;
} nd[maxl];

int n, m;

bool cmp(const node &a, const node &b) {
    if (a.p != b.p)
        return a.p < b.p;
    return a.y < b.y;
}

bool cmp2(const node &a, const node &b) {
    return a.idx < b.idx;
}

int main() {
    while (scanf("%d%d", &m, &n) != EOF) {
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &nd[i].p, &nd[i].y);
            nd[i].idx = i;
        }
        std::sort(nd + 1, nd + 1 + n, cmp);

        int rank = 0;
        for (int i = 1; i <= n; i++) {
            if (i == 1 || nd[i].p != nd[i-1].p)
                rank = 0;
            rank++;
            // printf("%d %d %d %d\n", i, nd[i].p, nd[i].y, rank);
            nd[i].rank = rank;
        }
        std::sort(nd + 1, nd + 1 + n, cmp2);
        for (int i = 1; i <= n; i++) {
            printf("%06d%06d\n", nd[i].p, nd[i].rank);
        }
    }

    return 0;
}

