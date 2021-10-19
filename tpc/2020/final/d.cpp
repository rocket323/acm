#include <stdio.h>
#include <cstring>

const int maxl = 1e5 + 10;
int t, n, f[maxl];

struct Node {
    int x, int y;
};

bool cmp(const Node &a, const Node &b) {
    if (a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}

void calc() {
    top = 0;
    s[top++] = 0;
    f[0] = 1;

    for (int i = 1; i < n; i++) {
        int l = 0, r = top - 1, ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            auto &x = e[s[mid]];
            auto &y = e[i];

            if (x.x < y.x && x.y < y.y) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (ans == -1) {
            f[i] = 0;
        } else {
            int j = s[ans];
        }
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &e[i].x, &e[i].y);
        }

        sort(e, e + n, cmp);
        calc();
    }
    return 0;
}
