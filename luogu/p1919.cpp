#include <algorithm>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e6 + 10;

char s[maxl], t[maxl];
int n, m;
vector<int> a, b;

using cd = complex<double>;
const double PI = acos(-1);

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

vector<int> mul(vector<int> &a, vector<int> &b) {
    vector<cd> fa(a.begin(), a.end());
    vector<cd> fb(b.begin(), b.end());
    int n = 1, m = a.size() + b.size() - 1;
    while (n < m)
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);
    vector<int> ans(m);
    for (int i = 0; i < ans.size(); i++) {
        ans[i] = round(fa[i].real());
    }
    return ans;
}

void out(vector<int> a) {
    for (int i = 0; i < a.size(); i++)
        printf("%d", a[i]);
    puts("");
}

int main() {
    scanf("%s", s);
    scanf("%s", t);
    n = strlen(s);
    m = strlen(t);
    a.resize(n);
    b.resize(m);
    for (int i = 0; i < n; i++) {
        a[i] = s[n - 1 - i] - '0';
    }
    for (int i = 0; i < m; i++) {
        b[i] = t[m - 1 - i] - '0';
    }
    auto ans = mul(a, b);
    int x = 0;
    while (x < ans.size()) {
        if (ans[x] >= 10) {
            if (x == ans.size() - 1) {
                ans.push_back(ans[x] / 10);
            } else {
                ans[x + 1] += ans[x] / 10;
            }
            ans[x] %= 10;
        }
        x++;
    }
    reverse(ans.begin(), ans.end());
    out(ans);
    return 0;
}