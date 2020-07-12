#include <stdio.h>
#include <cstring>
#include <algorithm>
#define maxl 1010
#define INF 0x3f3f3f3f
using namespace std;

int n, a[maxl];
int f[maxl], s[maxl], top;
bool up = true;

bool go(int i) {
    top = 0;
    s[top++] = i;
    up = true;
    for (int j = i + 1; j <= n; ++j) {
        if (a[j] < a[i]) continue;
        if (a[j] > a[s[top - 1]]) {
            if (!up) return false;
            s[top++] = j;
        } else {
            s[top++] = j;
            up = false;
        }
    }
    return top == (n - a[i] + 1);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }

        f[n] = 1;
        for (int i = n - 1; i >= 1; --i) {
            f[i] = 1;
            for (int j = i + 1; j <= n; ++j) {
                if (a[j] < a[i])
                    f[i] = max(f[i], f[j] + 1);
            }
            // printf("%d %d\n", i, f[i]);
        }

        int ans = 0;
        // 枚举第一个不移动的点
        for (int i = 1; i <= n; ++i) {
            // 1. 该点在最终的序列中是在下降段
            ans = max(ans, f[i]);
            // 2. 在上升段
            bool ok = go(i);
            if (!ok) continue;
            int p = s[top - 1];
            ans = max(ans, top + f[p] - 1);
        }

        printf("%d\n", n - ans);
    }

    return 0;
}

