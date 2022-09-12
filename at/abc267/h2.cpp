#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

typedef int64_t LL;
typedef uint64_t uLL;
typedef __int128_t sLL;
#define fir first
#define sec second
#define eb emplace_back
#define em emplace
#define pb push_back
#define ppb pop_back
#define pii std::pair<int, int>
#define mkp(a, b) std::make_pair(a, b)
#define bitcount(x) __builtin_popcount(x)
#define bitcountll(x) __builtin_popcountll(x)
#define bitparity(x) __builtin_parity(x)
#define bitparityll(x) __builtin_parityll(x)

int read() {
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}

LL readl() {
    LL s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}

///////////////////////////////////// wanna become a grandmaster

// #include <ext/pb_ds/tree_policy.hpp>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/hash_policy.hpp>
// #include <ext/rope>
// using namespace __gnu_cxx;
// using namespace __gnu_pbds;
// using rbtree = tree<int, null_type, std::less<int>, rb_tree_tag, tree_order_statistics_node_update> ;
// order_of_key() rank (return int) start from 0
// find_by_order() kth (return iterator) start from 0
// gp_hash_table<T1, T2> has_table

const int maxn = 1e5 + 10;
const int MOD = 998244353;

LL fpow(LL a, LL b) {
    LL ret = 1;
    while (b) {
        if (b & 1)
            ret = ret * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ret;
}

LL frac[maxn], ifrac[maxn], inv[maxn];

void init() {
    frac[0] = 1;
    for (int i = 1; i < maxn; i++) {
        frac[i] = frac[i - 1] * i % MOD;
    }
    ifrac[maxn - 1] = fpow(frac[maxn - 1], MOD - 2);
    for (int i = maxn - 2; i >= 0; i--) {
        ifrac[i] = ifrac[i + 1] * (i + 1) % MOD;
    }
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) {
        inv[i] = MOD - (LL)MOD / i * inv[MOD % i] % MOD;
    }
}

LL C(int a, int b) {
    if (a < b || b < 0)
        return 0;
    return frac[a] * ifrac[b] % MOD * ifrac[a - b] % MOD;
}

namespace NTT {

const int G = 3;  // base on 998244353 only

void NTT(std::vector<int> &a, const std::vector<int> &R, int type) {
    int lens = a.size();
    for (int i = 0; i < lens; i++) {
        if (i < R[i])
            std::swap(a[i], a[R[i]]);
    }
    for (int i = 1; i < lens; i <<= 1) {
        int gn = fpow(G, (MOD - 1) / (i << 1));
        for (int j = 0; j < lens; j += (i << 1)) {
            int g = 1;
            for (int k = 0; k < i; k++, g = (LL)g * gn % MOD) {
                int x = a[j + k], y = (LL)g * a[j + k + i] % MOD;
                a[j + k] = (x + y) % MOD;
                a[j + k + i] = (x - y + MOD) % MOD;
            }
        }
    }
    if (type == 1)
        return;
    int inv = fpow(lens, MOD - 2);
    if (lens > 1)
        std::reverse(++a.begin(), a.end());
    for (int i = 0; i < lens; i++) {
        a[i] = (LL)a[i] * inv % MOD;
    }
}

void NTT(std::vector<int> &a, std::vector<int> &b) {
    if (a.size() == 0)
        a.eb(0);
    if (b.size() == 0)
        b.eb(0);
    int n = a.size(), m = b.size();
    int lens = 1, L = 0;
    for (; lens < n + m - 1; lens <<= 1, L++)
        ;
    while (n < lens) {
        a.eb(0);
        ++n;
    }
    while (m < lens) {
        b.eb(0);
        ++m;
    }
    std::vector<int> R(lens);
    for (int i = 0; i < lens; i++) {
        R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
    }
    NTT(a, R, 1);
    NTT(b, R, 1);
    for (int i = 0; i < lens; i++) {
        a[i] = (LL)a[i] * b[i] % MOD;
    }
    NTT(a, R, -1);
}

};  // namespace NTT

int n, m;
int a[maxn];
int c[11];

void add(int &x, int val) {
    x += val;
    if (x >= MOD)
        x -= MOD;
    if (x < 0)
        x += MOD;
}

int32_t main() {
    init();
    n = read();
    m = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
        ++c[a[i]];
    }
    std::vector<int> f1(1, 0), f2(1, 0);
    f2[0] = 1;
    for (int i = 1; i <= 10; i++) {
        if (c[i] == 0)
            continue;
        std::vector<int> g1(c[i] + 1, 0), g2(c[i] + 1, 0);
        for (int j = 0; j <= c[i]; j++) {
            if (j & 1) {
                g1[j] = C(c[i], j);
            } else {
                g2[j] = C(c[i], j);
            }
        }
        std::vector<int> nf1(m + 1, 0), nf2(m + 1, 0);
        // printf("???\n");
        for (int j = 0; j < i; j++) {
            // printf("j = %d\n", j);
            std::vector<int> ff1, ff2;
            for (int k = j; k < (int)f1.size(); k += i) {
                ff1.eb(f1[k]);
            }
            for (int k = j; k < (int)f2.size(); k += i) {
                ff2.eb(f2[k]);
            }
            // printf("aaa\n");
            auto tf1 = ff1, tf2 = ff2, tf3 = ff1, tf4 = ff2;
            auto tg1 = g1, tg2 = g2;
            NTT::NTT(tf1, tg1);
            NTT::NTT(tf3, tg2);
            // printf("kkk\n");
            tg1 = g1;
            tg2 = g2;
            // printf("tf2.size() = %d, tg1.size() = %d\n", (int)tf2.size(), (int)tg1.size());
            NTT::NTT(tf2, tg1);
            // printf("()()\n");
            NTT::NTT(tf4, tg2);
            // printf("sss\n");
            if (tf1.size() > tf4.size())
                std::swap(tf1, tf4);
            if (tf3.size() > tf2.size())
                std::swap(tf3, tf2);
            // printf("hahha\n");
            int lens = tf1.size();
            for (int k = 0; k < lens; k++) {
                add(tf4[k], tf1[k]);
            }
            lens = tf3.size();
            for (int k = 0; k < lens; k++) {
                add(tf2[k], tf3[k]);
            }
            for (int k = 0; k < (int)tf4.size(); k++) {
                if (j + k * i > m)
                    break;
                add(nf2[j + k * i], tf4[k]);
            }
            for (int k = 0; k < (int)tf2.size(); k++) {
                if (j + k * i > m)
                    break;
                add(nf1[j + k * i], tf2[k]);
            }
        }
        std::swap(f1, nf1);
        std::swap(f2, nf2);
        while (f1.size() && f1.back() == 0)
            f1.pop_back();
        while (f2.size() && f2.back() == 0)
            f2.pop_back();
        // printf("i = %d\n", i);
        // printf("f1 = ");
        // for (const auto &val : f1) {
        //     printf("%d ", val);
        // }
        // printf("\n");
        // printf("f2 = ");
        // for (const auto &val : f2) {
        //     printf("%d ", val);
        // }
        // printf("\n");
    }
    if (f1.size() <= m) {
        printf("0\n");
        return 0;
    }
    printf("%d\n", f1[m]);
    return 0;
}

/*
    读入是否需要开LL?
    是否存在退化、特判的情况?
    多组数据时是否清空完整?
*/