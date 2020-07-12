#include <stdio.h>
#include <cstring>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

const int maxl = 105;
const int mod = 1e9 + 7;

struct node {
    int d, l, r;
};

vector<node> v;

int main() {
    char a[maxl][maxl];
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        v.clear();
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%s", a[i]);
            for (int j = 0; j < n; ++j) {
                cnt += (a[i][j] == '1');
            }
        }

        int top = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (a[i][j] == '1') {
                    int l = i, r = i;
                    a[i][j] = '0';
                    while (r + 1 < n && a[r + 1][j] == '1') {
                        a[r + 1][j] = '0';
                        r++;
                    }
                    node nd = {j + 1, l + 1, r + 1};
                    v.push_back(nd);
                }
            }
        }
        cout << v.size() << endl;
        for (int i = 0; i < v.size(); ++i) {
            printf("0 1 0 1 0 1 %d %d %d\n", v[i].d, v[i].l, v[i].r);
        }
    }

    return 0;
}

