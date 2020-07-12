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
const int mod = 1e9 + 7;

int t, x, y;
int ca, cb;
char s[maxl];

struct node {
    char ch;
    int cnt;
    string print() {
        return string(cnt, ch);
    }
};

void solve(char a, char b, int ca, int cb, int ka, int kb, string &ans, int &cnt) {
    int ga = ca / ka, gb = cb / kb;
    int ma = ca % ka, mb = cb % kb;
    int tota = ga + (ma > 0);
    vector<node> va;
    vector<node> vb;

    for (int i = 0; i < tota; ++i) {
        if (i < ca % tota)
            va.push_back({a, ca / tota + 1});
        else
            va.push_back({a, ca / tota});
    }

    if (cb < tota - 1) {
        for (int i = 0; i < cb; ++i)
            vb.push_back({b, 1});
        for (int i = cb; i < tota - 1; ++i) {
            vb.push_back({'*', 1});
            cnt++;
        }
    } else if (cb < (tota - 1) * kb) {
        for (int i = 0; i < tota - 1; ++i) {
            if (i < cb % (tota - 1))
                vb.push_back({b, cb / (tota - 1) + 1});
            else
                vb.push_back({b, cb / (tota - 1)});
        }
    } else {
        for (int i = 0; i < tota - 1; ++i)
            vb.push_back({b, kb});
        cb -= (tota - 1) * kb;
        if (cb <= kb) {
            vb.push_back({b, cb});
        } else {
            vb.push_back({b, kb});
            cb -= kb;
            while (cb > 0) {
                vb.push_back({'*', 1});
                cnt++;
                if (cb <= kb) {
                    vb.push_back({b, cb});
                    cb = 0;
                } else {
                    vb.push_back({b, kb});
                    cb -= kb;
                }
            }
        }
    }

    for (int i = 0; i < tota; ++i) {
        ans += va[i].print();
        if (i < vb.size())
            ans += vb[i].print();
    }
    for (int i = tota; i < vb.size(); ++i)
        ans += vb[i].print();
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        scanf("%d%d", &x, &y);
        ca = 0, cb = 0;

        for (int i = 0; s[i]; ++i) {
            if (s[i] == 'a')
                ca++;
            else
                cb++;
        }

        int cnt1 = 0, cnt2 = 0;
        string ans1 = "", ans2 = "";
        solve('a', 'b', ca, cb, x, y, ans1, cnt1);
        solve('b', 'a', cb, ca, y, x, ans2, cnt2);

        if (cnt1 <= cnt2) {
            puts(ans1.c_str());
        } else {
            puts(ans2.c_str());
        }
    }

    return 0;
}

