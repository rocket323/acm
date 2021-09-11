#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int maxl = 205;
int n;
char s[maxl][maxl], t[maxl][maxl], a[maxl][maxl];
vector<pair<int, int>> ps, pt;

void rotate(char s[maxl][maxl]) {
    for (int j = n - 1; j >= 0; j--) {
        for (int i = 0; i < n; i++) {
            a[n - 1 - j][i] = s[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            s[i][j] = a[i][j];
    }
}

bool same(char s[maxl][maxl], char t[maxl][maxl]) {
    ps.clear();
    pt.clear();

    int sr = -1, sc = -1, tr = -1, tc = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[i][j] == '#') {
                if (sr == -1) {
                    sr = i;
                    sc = j;
                } else {
                    ps.push_back(make_pair(i - sr, j - sc));
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (t[i][j] == '#') {
                if (tr == -1) {
                    tr = i;
                    tc = j;
                } else {
                    pt.push_back(make_pair(i - tr, j - tc));
                }
            }
        }
    }

    if (ps.size() != pt.size())
        return false;

    for (int i = 0;  i < ps.size(); i++) {
        if (ps[i] != pt[i])
            return false;
    }

    return true;
}

bool gao() {
    for (int i = 0; i < 4; i++) {
        rotate(s);
        if (same(s, t) || same(t, s))
            return true;
    }
    return false;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%s", s[i]);
        for (int i = 0; i < n; i++)
            scanf("%s", t[i]);

        puts(gao() ? "Yes" : "No");
    }
    return 0;
}

