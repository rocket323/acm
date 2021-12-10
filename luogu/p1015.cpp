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
const int maxl = 1e4 + 10;

int n, m, mod;
char str[100];

struct HP {
    vector<int> s;
    HP() {
        *this = 0;
    }
    HP(int n) {
        *this = n;
    }
    HP(const char *str) {
        *this = str;
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
    void rev() {
        reverse(s.begin(), s.end());
        trunc();
    }
    friend ostream &operator<<(ostream &cout, const HP &x) {
        for (int i = x.s.size() - 1; i >= 0; i--)
            cout << x.s[i];
        return cout;
    }
    HP operator=(int n) {
        if (n == 0) {
            s.push_back(0);
        } else {
            while (n) {
                s.push_back(n % mod);
                n /= 10;
            }
        }
        return *this;
    }
    HP operator=(const char *str) {
        int len = strlen(str);
        for (int i = len - 1; i >= 0; i--) {
            s.push_back(str[i] - '0');
        }
        return *this;
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

    bool check() {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            if (s[i] != s[n - 1 - i])
                return false;
        }
        return true;
    }
};

int main() {
    scanf("%d%s", &n, str);
    mod = n;
    HP x = m;
    int len = strlen(str);
    for (int i = len - 1; i >= 0; i--) {
        if (str[i] >= '0' && str[i] <= '9')
            x[len - 1 - i] = str[i] - '0';
        else
            x[len - 1 - i] = str[i] - 'A' + 10;
    }

    for (int i = 0; i <= 30; i++) {
        if (x.check()) {
            printf("STEP=%d\n", i);
            return 0;
        }
        HP a = x;
        HP b = x;
        b.rev();
        HP c = a + b;
        x = c;
    }
    puts("Impossible!");

    return 0;
}
