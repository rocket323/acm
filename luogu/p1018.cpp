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

struct HP {
    static const int mod = 10;
    vector<int> s;
    HP() {
        *this = 0;
    }
    HP(int n) {
        *this = n;
    }
    HP(const char *str) {
        parse(str, strlen(str));
    }
    HP(const char *str, int len) {
        parse(str, len);
    }
    HP operator=(int n) {
        parse(n);
        return *this;
    }
    HP operator=(const char *str) {
        parse(str, strlen(str));
        return *this;
    }
    void parse(const char *str, int len) {
        s.clear();
        for (int i = len - 1; i >= 0; i--) {
            s.push_back(str[i] - '0');
        }
    }
    void parse(int n) {
        s.clear();
        if (n == 0) {
            s.push_back(0);
        } else {
            while (n) {
                s.push_back(n % mod);
                n /= 10;
            }
        }
    }
    int &operator[](int idx) {
        if (idx >= s.size())
            s.resize(idx + 1);
        return s[idx];
    }
    void trunc() {
        while (s.size() > 1 && s.back() == 0)
            s.pop_back();
    }
    HP operator+(const HP &b) {
        HP c;
        int i = 0, n = s.size(), m = b.s.size();
        for (i = 0; i < n || i < m || c[i]; i++) {
            if (i < n)
                c[i] += s[i];
            if (i < m)
                c[i] += b.s[i];
            c[i + 1] = c[i] / mod;
            c[i] %= mod;
        }
        c.trunc();
        return c;
    }
    HP operator*(const HP &b) {
        HP c;
        int n = s.size(), m = b.s.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                c[i + j] += s[i] * b.s[j];
            }
        }
        for (int i = 0; i < n + m; i++) {
            c[i + 1] += c[i] / mod;
            c[i] %= mod;
        }
        c.trunc();
        return c;
    }
    friend bool operator<(const HP &a, const HP &b) {
        if (a.s.size() != b.s.size())
            return a.s.size() < b.s.size();
        for (int i = a.s.size() - 1; i >= 0; i--) {
            if (a.s[i] != b.s[i])
                return a.s[i] < b.s[i];
        }
        return false;
    }
    friend ostream &operator<<(ostream &cout, const HP &x) {
        for (int i = x.s.size() - 1; i >= 0; i--)
            cout << x.s[i];
        return cout;
    }
};

int n, k;
char s[maxl];
HP f[105][10];
int vis[105][10];

HP get_int(int x, int y) {
    return HP(s + x - 1, y - x + 1);
}

int main() {
    scanf("%d%d", &n, &k);
    scanf("%s", s);

    memset(vis, 0, sizeof vis);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k + 1; j++) {
            f[i][j] = 0;
        }
    }
    vis[0][0] = 1;
    f[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            if (!vis[i][j])
                continue;

            for (int x = i + 1; x <= n; x++) {
                HP p = get_int(i + 1, x);
                f[x][j + 1] = max(f[x][j + 1], f[i][j] * p);
                vis[x][j + 1] = 1;
            }
        }
    }
    cout << f[n][k + 1] << endl;
    return 0;
}