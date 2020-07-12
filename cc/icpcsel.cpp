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
const int maxl = 200010;
const int mod = 1e9 + 7;

int tc, n, m, k;
map<string, int> mp;

struct team {
    string name;
    int rank;
    int srank;
} t[maxl];

bool cmp(const team &a, const team &b) {
    return a.srank < b.srank || (a.srank == b.srank && a.rank < b.rank);
}

bool cmp2(const team &a, const team &b) {
    return a.rank < b.rank;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> tc;
    while (tc--) {
        mp.clear();
        cin >> n >> m >> k;
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> t[i].name >> s;
            t[i].rank = i + 1;
            mp[s]++;
            t[i].srank = mp[s];
        }
        sort(t, t + n, cmp);

        bool flag = true;
        for (int i = 0; i < m; ++i) {
            if (t[i].srank > k) {
                flag = false;
                break;
            }
        }
        if (flag) {
            sort(t, t + m, cmp2);
            for (int i = 0; i < m; ++i)
                cout << t[i].name << endl;
        } else {
            cout << "Impossible" << endl;
        }
        cout << endl;
    }

    return 0;
}

