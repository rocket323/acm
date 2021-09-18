#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

const int maxl = 1e5 + 10;
char x[maxl], s[20];
int n, ord[30];
vector<string> t;

bool cmp(const string &a, const string &b) {
    int m = min(a.length(), b.length());
    for (int i = 0; i < m; i++) {
        int cha = a[i] - 'a', chb = b[i] - 'a';
        if (ord[cha] != ord[chb]) {
            return ord[cha] < ord[chb];
        }
    }

    return a.length() < b.length();
}

int main() {
    scanf("%s", x);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        t.push_back(s);
    }
    for (int i = 0; x[i]; i++) {
        int a = x[i] - 'a';
        ord[a] = i;
    }

    sort(t.begin(), t.end(), cmp);
    for (int i = 0; i < t.size(); i++) {
        cout << t[i] << endl;
    }
    return 0;
}
