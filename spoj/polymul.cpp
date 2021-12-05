#include <algorithm>
#include <cstdio>
#include <cstring>
#include <complex>
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

using cd = complex<double>;
const double PI = acos(-1);
int t, n, m;

void fft(vector<cd> &a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    fft(a0, invert);
    fft(a1, invert);
    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

void gao(vector<int> &a, vector<int> &b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);
    vector<cd> ans(fa.begin(), fa.begin() + 2 * m + 1);
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        ll x = round(ans[i].real());
        printf("%lld%c", x, i == ans.size() - 1 ? '\n' : ' ');
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        m = n;
        vector<int> a(n + 1), b(n + 1);
        for (int i = n; i >=  0; i--) {
            scanf("%d", &a[i]);
        }
        for (int i = n; i >= 0; i--) {
            scanf("%d", &b[i]);
        }
        gao(a, b);
    }

    return 0;
}

