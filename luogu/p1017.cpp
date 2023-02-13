#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int n, r, R;
int a[20], top;

void gao1(int n, int r) {
    top = 0;
    while (n) {
        a[top++] = n % r;
        n /= r;
    }
}

void extend(int p) {
    if (p >= top)
        top = p + 1;
}

void gao2(int r, int idx) {
    int p = idx;
    while (p < top || a[p] > 0) {
        if (a[p] >= r) {
            a[p + 1] += a[p] / r;
            a[p] %= r;
            extend(p + 1);
        }
        if (a[p] > 0) {
            int x = r + a[p];
            a[p + 1] += x / r;
            a[p] = r - a[p];
            extend(p + 1);
        }
        if (a[p + 1] >= r) {
            a[p + 2] += a[p + 1] / r;
            a[p + 1] = a[p + 1] % r;
            extend(p + 2);
        }
        p += 2;
    }
}

void out() {
    for (int i = top - 1; i >= 0; i--) {
        char c = a[i] > 9 ? 'A' + a[i] - 10 : '0' + a[i];
        printf("%c", c);
    }
}

int main() {
    cin >> n >> r;
    R = -r;
    gao1(n > 0 ? n : -n, R);
    if (n >= 0) {
        gao2(R, 1);
    } else {
        gao2(R, 0);
    }
    printf("%d=", n);
    out();
    printf("(base%d)\n", r);
    return 0;
}
