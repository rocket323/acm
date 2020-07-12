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

int t, n, m;
vector<int> a, b;

bool isSame(vector<int> &a, vector<int> &b) {
    if (a.size() != b.size())
        return false;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        a.clear();
        b.clear();
        scanf("%d%d", &n, &m);
        int v;
        for (int i = 0; i < n; i++) {
            scanf("%d", &v);
            if (v > 0) a.push_back(v);
        }
        for (int j = 0; j < m; j++) {
            scanf("%d", &v);
            if (v > 0) b.push_back(v);
        }

        if (isSame(a, b))
            puts("Bob");
        else
            puts("Alice");
    }

    return 0;
}

