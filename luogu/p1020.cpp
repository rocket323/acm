#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;

int n, a[maxl], x;
int b[maxl], top;

int gao1() {
    top = 0;
    for (int i = 1; i <= n; i++) {
        int l = 0, r = top - 1, idx = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (b[mid] < a[i]) {
                idx = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        if (idx == -1)
            b[top++] = a[i];
        else
            b[idx] = a[i];
    }

    return top;
}

int gao2() {
    top = 0;
    for (int i = 1; i <= n; i++) {
        int idx = lower_bound(b, b + top, a[i]) - b;
        if (idx == top) {
            b[top++] = a[i];
        } else {
            b[idx] = a[i];
        }
    }
    return top;
}

int main() {
    n = 0;
    while (scanf("%d", &x) != EOF) {
        a[++n] = x;
    }
    printf("%d\n%d\n", gao1(), gao2());

    return 0;
}
