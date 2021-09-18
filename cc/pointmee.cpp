#include <math.h>
#include <stdio.h>
#include <algorithm>
#include <cstring>
using namespace std;

#define eps 1e-8
#define zero(x) (fabs(x) < eps)
#define SGN(x) ((x) > eps ? 1 : ((x) > -eps ? 0 : -1))
#define _sign(x) ((x) > eps ? 1 : ((x) < -eps ? 2 : 0))

using ll = long long;

const int maxl = 105;
const int inf = 0x3f3f3f3f;
int t, n, ans;

struct pt {
    double x, y;
    pt() {
    }
    pt(double _x, double _y) : x(_x), y(_y) {
    }
    pt operator-(const pt p1) {
        return pt(x - p1.x, y - p1.y);
    }
    pt operator+(const pt p1) {
        return pt(x + p1.x, y + p1.y);
    }
    pt operator*(double s) {
        return pt(x * s, y * s);
    }
    pt operator/(double s) {
        return pt(x / s, y / s);
    }
    bool operator<(const pt p1) const {
        return y < p1.y - eps || y < p1.y + eps && x < p1.x;
    }
    bool operator==(const pt p1) const {
        return !SGN(y - p1.y) && !SGN(x - p1.x);
    }
    bool operator!=(const pt p1) const {
        return SGN(y - p1.y) || SGN(x - p1.x);
    }
} p[maxl];

double cpr(const pt &a, const pt &b, const pt &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
double dpr(const pt &a, const pt &b, const pt &c) {
    return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y);
}
double cpr(const pt &a, const pt &b) {
    return a.x * b.y - a.y * b.x;
}
double dpr(const pt &a, const pt &b) {
    return a.x * b.x + a.y * b.y;
}

pt its(pt a, pt b, pt c, pt d) {
    double v1 = cpr(a, b, c), v2 = cpr(a, b, d);
    return (c * v2 - d * v1) / (v2 - v1);
}

pt d[4] = {pt(0, 1), pt(1, 1), pt(1, 0), pt(1, -1)};
pt e[4] = {pt(0, -1), pt(-1, -1), pt(-1, 0), pt(-1, 1)};

bool in_line(pt p1, pt p2, pt p3) {
    double c = cpr(p1, p2, p3);
    return zero(c);
}

int step(pt p1, pt p2) {
    if (p1 == p2)
        return 0;

    for (int i = 0; i < 4; i++) {
        pt a = p1, b = p1 + d[i];

        if (in_line(a, b, p2))
            return 1;
    }

    return 2;
}

int gao(pt p1) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int tmp = step(p[i], p1);
        if (tmp == inf)
            return inf;
        ans += tmp;
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%lf", &p[i].x);
        }
        for (int i = 0; i < n; i++) {
            scanf("%lf", &p[i].y);
        }

        ans = inf;
        for (int i = 0; i < n; i++) {
            int tmp = gao(p[i]);
            ans = min(ans, tmp);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j)
                    continue;

                for (int k1 = 0; k1 < 4; k1++) {
                    for (int k2 = 0; k2 < 4; k2++) {
                        if (k1 == k2)
                            continue;

                        pt a = p[i], b = p[i] + d[k1];
                        pt c = p[j], dd = p[j] + d[k2];
                        pt e = its(a, b, c, dd);
                        int tmp = gao(e);
                        ans = min(ans, tmp);
                    }
                }
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}
