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

int tc, n, q;
string s[maxl], t[maxl];
set<string> st;

int main() {
    scanf("%d", &tc);
    for (int x = 1; x <= tc; x++) {
        scanf("%d\n", &n);
        for (int i = 0; i < n; i++) {
            getline(cin, s[i]);
        }
        scanf("%d\n", &q);
        for (int i = 0; i < q; i++) {
            getline(cin, t[i]);
        }
        int ans = 0;
        st.clear();
        for (int i = 0; i < q; i++) {
            if (!st.count(t[i])) {
                if (st.size() == n - 1) {
                    ans++;
                    st.clear();
                }
                st.insert(t[i]);
            }
        }
        printf("Case #%d: %d\n", x, ans);
    }
    return 0;
}