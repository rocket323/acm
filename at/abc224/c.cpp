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

struct pt {
    int x, y;
    pt() {
    }
    pt(int _x, int _y) : x(_x), y(_y) {
    }
    pt operator-(const pt p1) {
        return pt(x - p1.x, y - p1.y);
    }
    pt operator+(const pt p1) {
        return pt(x + p1.x, y + p1.y);
    }
    pt operator*(int s) {
        return pt(x * s, y * s);
    }
    pt operator/(int s) {
        return pt(x / s, y / s);
    }
} p[maxl];

int cpr(const pt &a, const pt &b, const pt &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int n;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            for (int k = j+1; k < n; k++) {
                int x = cpr(p[i], p[j], p[k]);
                // printf("%d %d %d %d\n", i, j, k, x);
                if (x != 0) {
                    ans++;
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}

