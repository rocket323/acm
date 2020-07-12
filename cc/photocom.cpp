#include <stdio.h>
#include <cstring>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#define maxl 1000010
#define ll long long

ll n1, m1, n2, m2, t;
int mat1[maxl];
int mat2[maxl];
int mat3[maxl];
char str[maxl];
ll dn, dm, tn, tm;
ll s[2][maxl];
int rcnt[2][maxl], ccnt[2][maxl];

struct Rect {
    ll r1, r2;
    ll c1, c2;
} rects1[maxl], rects2[maxl];

ll gcd(ll a, ll b) {
    if (a < b) std::swap(a, b);
    if (b == 0) return a;
    return gcd(b, a % b);
}

void getRect(ll n, ll m, ll r, ll c, Rect &rect) {
    ll spanRow = tn / n;
    ll spanCol = tm / m;
    rect.r1 = spanRow * r;
    rect.r2 = spanRow * (r + 1) - 1;
    rect.c1 = spanCol * c;
    rect.c2 = spanCol * (c + 1) - 1;
}

#define get(v, r, c) (((r) >= 0 && (c) >= 0) ? s[v][(r) * m2 + (c)] : 0)
#define IDX(r, c) ((r) * m2 + (c))
#define IDX2(c, r) ((c) * n2 + (r))

void init() {
    scanf("%lld%lld", &n1, &m1);
    scanf("%s", str);
    for (int i = 0; i < n1; i++) {
        for (ll j = 0; j < m1; j++) {
            ll idx = i * m1 + j;
            mat1[idx] = str[idx] - '0';
        }
    }

    scanf("%lld%lld", &n2, &m2);
    scanf("%s", str);
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < m2; j++) {
            ll idx = i * m2 + j;
            mat2[idx] = str[idx] - '0';
        }
    }

    if (n1 > n2) {
        for (int i = 0; i < n1 * m1; i++) mat3[i] = mat1[i];
        for (int i = 0; i < n2 * m2; i++) mat1[i] = mat2[i];
        for (int i = 0; i < n1 * m1; i++) mat2[i] = mat3[i];

        std::swap(n1, n2);
        std::swap(m1, m2);
    }

    dn = gcd(n1, n2), dm = gcd(m1, m2);
    tn = n1 / dn * n2, tm = m1 / dm * m2;

    ll spanRow = tn / n2, spanCol = tm / m2;
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < m2; j++) {
            int idx = i * m2 + j;
            int v = mat2[idx];
            s[0][idx] = get(0, i-1, j) + get(0, i, j-1) - get(0, i-1, j-1);
            s[1][idx] = get(1, i-1, j) + get(1, i, j-1) - get(1, i-1, j-1);

            s[v][idx] += spanRow * spanCol;
        }
    }

    for (int i = 0; i < n1; i++)
        for (int j = 0; j < m1; j++)
            getRect(n1, m1, i, j, rects1[i * m1 + j]);

    for (int i = 0; i < n2; i++)
        for (int j = 0; j < m2; j++)
            getRect(n2, m2, i, j, rects2[i * m2 + j]);

    for (int r = 0; r < n2; r++) {
        for (int c = 0; c < m2; c++) {
            int idx = IDX(r, c);
            int v = mat2[idx];
            rcnt[v][idx] = 1;
            rcnt[v^1][idx] = 0;
            if (c > 0) {
                rcnt[v][idx] += rcnt[v][idx - 1];
                rcnt[v^1][idx] += rcnt[v^1][idx - 1];
            }
        }
    }

    for (int c = 0; c < m2; c++) {
        for (int r = 0; r < n2; r++) {
            int v = mat2[IDX(r, c)];
            int idx = IDX2(c, r);
            ccnt[v][idx] = 1;
            ccnt[v^1][idx] = 0;
            if (r > 0) {
                ccnt[v][idx] += ccnt[v][idx - 1];
                ccnt[v^1][idx] += ccnt[v^1][idx - 1];
            }
        }
    }
}

#define RECT1(r, c) (rects1[(r) * m1 + (c)])
#define RECT2(r, c) (rects2[(r) * m2 + (c)])

inline ll rectSum(int v, ll r1, ll r2, ll c1, ll c2) {
    if (r1 > r2 || c1 > c2) return 0;
    ll ans = s[v][IDX(r2, c2)]
        - (r1 > 0 ? s[v][IDX(r1 - 1, c2)] : 0)
        - (c1 > 0 ? s[v][IDX(r2, c1 - 1)] : 0)
        + ((r1 > 0 && c1 > 0) ? s[v][IDX(r1 - 1, c1 - 1)] : 0);
    return ans;
}

inline ll rowCnt(int v, int r, int c1, int c2) {
    assert(c1 <= c2);
    return rcnt[v][IDX(r, c2)] - (c1 > 0 ? rcnt[v][IDX(r, c1 - 1)] : 0);
}

inline ll colCnt(int v, int c, int r1, int r2) {
    assert(r1 <= r2);
    return ccnt[v][IDX2(c, r2)] - (r1 > 0 ? ccnt[v][IDX2(c, r1 - 1)] : 0);
}

void solve() {
    ll ans = 0;
    ll lastR = 0, lastC = 0;
    ll curR1 = 0, curR2 = 0, curC1 = 0, curC2 = 0;

    ll csum = 0, rsum = 0;
    ll spanRow = tn / n2, spanCol = tm / m2;
    int llen = 0, rlen = 0, ulen = 0, dlen = 0;
    int v = 0;

    for (int i = 0; i < n1; i++) {
        Rect &rect1 = RECT1(i, 0);

        curR1 = lastR, curR2 = lastR;
        while (curR2 + 1 < n2) {
            Rect &rect2 = RECT2(curR2 + 1, 0);
            if (rect2.r1 > rect1.r2) break;
            curR2++;
        }
        lastR = curR2;

        lastC = 0;
        for (int j = 0; j < m1; j++) {
            Rect &rect1 = RECT1(i, j);

            curC1 = lastC, curC2 = lastC;
            while (curC2 + 1 < m2) {
                Rect &rect2 = RECT2(0, curC2 + 1);
                if (rect2.c1 > rect1.c2) break;
                curC2++;
            }
            lastC = curC2;
            v = mat1[i * m1 + j];

            ll tmp = rectSum(v, curR1, curR2, curC1, curC2);
            ans += tmp;
            auto &ul = RECT2(curR1, curC1);
            auto &ur = RECT2(curR1, curC2);
            auto &dl = RECT2(curR2, curC1);
            auto &dr = RECT2(curR2, curC2);

            llen = 0, rlen = 0, ulen = 0, dlen = 0;
            if (ur.r1 < rect1.r1) ulen = std::min(rect1.r1 - 1, ur.r2) - ur.r1 + 1;
            if (dr.r2 > rect1.r2) dlen = dr.r2 - std::max(rect1.r2 + 1, dr.r1) + 1;

            if (ul.c1 < rect1.c1) {
                llen = std::min(rect1.c1 - 1, ul.c2) - ul.c1 + 1;
                if (llen > 0 && ulen > 0 && mat2[IDX(curR1, curC1)] == v) ans += llen * ulen;
                if (llen > 0 && dlen > 0 && mat2[IDX(curR2, curC1)] == v) ans += dlen * llen;
            }
            if (ur.c2 > rect1.c2) {
                rlen = ur.c2 - std::max(rect1.c2 + 1, ur.c1) + 1;
                if (rlen > 0 && ulen > 0 && mat2[IDX(curR1, curC2)] == v) ans += rlen * ulen;
                if (rlen > 0 && dlen > 0 && mat2[IDX(curR2, curC2)] == v) ans += dlen * rlen;
            }

            if (llen > 0) ans -= spanRow * llen * colCnt(v, curC1, curR1, curR2);
            if (rlen > 0) ans -= spanRow * rlen * colCnt(v, curC2, curR1, curR2);
            if (ulen > 0) ans -= spanCol * ulen * rowCnt(v, curR1, curC1, curC2);
            if (dlen > 0) ans -= spanCol * dlen * rowCnt(v, curR2, curC1, curC2);
        }
    }

    printf("%lld\n", ans);
}

int main() {
    scanf("%lld", &t); while (t--) {
        init();
        solve();
    }
    return 0;
}

