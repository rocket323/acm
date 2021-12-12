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
const int maxl = 1e5 + 10;

int n;
map<string, int> mp;
string s;
char t[100];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", t);
        s = t;
        mp[s]++;
    }

    string ans;
    int mx = 0;
    for (auto && kv : mp) {
        if (mx == 0 || kv.second > mx) {
            mx = kv.second;
            ans = kv.first;
        }
    }

    cout << ans << endl;
    return 0;
}

