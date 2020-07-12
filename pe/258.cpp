#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 20092010;

class BM {
public:
    int power(int x, int y) {
        int ans = 1, t = x;
        while (y) {
            if (y & 1) ans = ((ll)ans * t) % mod;
            t = (ll)t * t % mod;
            y >>= 1;
        }
    }
    void solve(int val[]) {
        cnt = 0;
        ans[0].clear();
        n = val.size();
        for (int i = 1; i <= n; i++) {
            int now = val[i];
            for (int j = 0; j < ans[cnt].size(); j++)
                now = (now - (ll)val[i - j - 1] * ans[cnt][j] % mod + mod) % mod;

            delta[i] = now;
            if (now == 0)
                continue;
            fail[cnt] = i;
            if (cnt == 0) {
                ans[++cnt].clear();
                ans[cnt].resize(i);
                continue;
            }
            ans[++cnt].clear();
            ans[cnt].resize(i - fail[cnt - 2] - 1);
            int mul = (ll)now * power(delta[fail[cnt - 2]], mod - 2) % mod;
            ans[cnt].push_back(mul);
            for (int j = 0; j < ans[cnt - 2].size(); j++)
                ans[cnt].push_back((ll)ans[cnt - 2][j] * (mod - mul) % mod);
            if (ans[cnt].size() < ans[cnt - 1].size())
                ans[cnt].resize(ans[cnt - 1].size());
            for (int j = 0; j < ans[cnt - 1].size(); j++)
                ans[cnt][j] = (ans[cnt][j] + ans[cnt - 1][j]) % mod;
        }
    }

private:
    static const int maxn = 5005;
    int n, cnt, fail[maxl], delta[maxn];
    vector<int> ans[maxl];
};

/*
 * h[i] = a[0]*h[i-1] + a[1]*h[i-2] + ... + a[k-1]*h[i-k], i >= k
 */
class CayleyHamilton {
public:
    CayleyHamilton(vector<int> &a_, vector<int> &h_) : 
        a(move(a_)), h(move(h_)), k(a.size()) {}

    void mul(vector<int> &x, vector<int> &y) {
        vector<int> tmp(2 * k);
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                tmp[i + j] = (tmp[i + j] + (ll)x[i] * y[j]) % mod;
            }
        }

        for (int i = 2 * k - 2; i >= k; i--) {
            for (int j = 1; j <= k; j++) {
                tmp[i - j] = (tmp[i - j] + (ll)tmp[i] * a[j-1]) % mod;
            }
        }

        for (int i = 0; i < k; i++)
            x[i] = tmp[i];
    }

    int calc(ll n) {
        if (n < k)
            return h[n];
        n -= (k - 1);

        vector<int> res(k), t(k);
        res[0] = t[1] = 1;
        while (n) {
            if (n & 1) mul(res, t);
            mul(t, t);
            n >>= 1;
        }

        h.resize(2 * k);
        for (int i = k; i <= 2 * k - 2; i++) {
            for (int j = 1; j <= k; j++) {
                h[i] = (h[i] + (ll)a[j - 1] * h[i - j]) % mod;
            }
        }

        int ans = 0;
        for (int i = 0; i < k; i++) {
            int x = (ll)res[i] * h[k - 1 + i] % mod;
            ans = (ans + x) % mod;
        }

        return ans;
    }

private:
    vector<int> a, h;
    int k;
};

const int N = 1000000;
int f[N + 10];

int main() {
    int k = 2000;
    vector<int> h(k), a(k);
    for (int i = 0; i < k; i++)
        f[i] = h[i] = 1;

    for (int i = k; i < N; i++)
        f[i] = (f[i - 2000] + f[i - 1999]) % mod;

    a[k-1] = a[k-2] = 1;
    ll n = 1e18;
    CayleyHamilton ch(a, h);
    cout << ch.calc(n) << endl;

    return 0;
}

