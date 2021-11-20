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
const int maxl = 1048576 + 10;

int q, nxt[maxl], pre[maxl];
int t;
ll x;
ll a[maxl];

int ffind(int h) {
    if (a[h] != -1) {
        return nxt[h] = ffind(nxt[h]);
    }
    return h;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n = 1048576;
    for (int i = 0; i < n; i++) {
        a[i] = -1;
    }
    for (int i = 0; i < n - 1; i++)
        nxt[i] = i + 1;
    nxt[n-1] = 0;
    for (int i = 1; i < n; i++)
        pre[i] = i - 1;
    pre[0] = n - 1;

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> t >> x;
        if (t == 1) {
            int h = x % n;
            int d = ffind(h);
            // while (a[d] != -1) {
            //     d = nxt[d];
            // }
            nxt[pre[d]] = nxt[d];
            pre[nxt[d]] = pre[d];
            a[d] = x;
        } else {
            int h = x % n;
            cout << a[h] << endl;
        }
    }

    return 0;
}

