#include <algorithm>
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
const int maxl = 2e5 + 10;

int t, n, top, last[100];
string s[maxl];

bool gao() {
    for (int i = 1; i <= top; i++) {
        for (int j = 1; j <= top; j++) {
            if (i == j)
                continue;
            int x = s[i].length();
            int y = s[j].length();
            if (s[i][x - 1] == s[j][0] && s[i][x - 1] == s[j][y - 1]) {
                s[i] += s[j];
                s[j] = s[top];
                top--;
                return true;
            }
        }
        for (int j = 1; j <= top; j++) {
            if (i == j)
                continue;
            int x = s[i].length();
            if (s[i][x - 1] == s[j][0]) {
                s[i] += s[j];
                s[j] = s[top];
                top--;
                return true;
            }
        }
    }
    return false;
}

bool check(string &a) {
    memset(last, -1, sizeof last);
    for (int i = 0; i < a.length(); i++) {
        int x = a[i] - 'A';
        if (last[x] != -1) {
            if (last[x] + 1 != i)
                return false;
        }
        last[x] = i;
    }
    return true;
}

int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d", &n);
        top = n;
        for (int i = 1; i <= n; i++) {
            cin >> s[i];
        }
        while (top > 1) {
            bool flag = gao();
            if (!flag)
                break;
        }

        string ans = "";
        for (int i = 1; i <= top; i++)
            ans += s[i];
        cout << "Case #" << tc << ": ";
        if (check(ans))
            cout << ans << endl;
        else
            cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}