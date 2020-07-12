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

int t, n;
string a, b;
map<string, string> nxt;
map<string, int> d;

int main() {
    scanf("%d", &t);
    while (t--) {
        nxt.clear();
        d.clear();
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            cin >> a >> b;
            d[a] = d[a];
            d[b]++;
            nxt[a] = b;
        }
        string s;
        for (auto iter = d.begin(); iter != d.end(); ++iter)
            if (iter->second == 0)
                s = iter->first;

        std::vector<string> v;
        while (s.length() > 0) {
            v.push_back(s);
            s = nxt[s];
        }
        for (int i = 0; i < v.size() - 1; ++i)
            printf("%s-%s%c", v[i].c_str(), v[i + 1].c_str(), (i == v.size() - 1) ? '\n' : ' ');
    }

    return 0;
}

