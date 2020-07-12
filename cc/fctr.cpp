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

ll n, m;
int t;
std::vector<std::pair<int, int>> ans;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%lld%lld", &n, &m);
        ans.clear();
        for (int i = 2; (ll)i * i <= n; i++) {
            if (n % i == 0) {
                int cnt = 0;
                while (n % i == 0) {
                    cnt++;
                    n /= i;
                }
                ans.push_back(std::make_pair(i, cnt));
            }
        }
        if (n > 1) {
            ans.push_back(std::make_pair((int)n, 1));
        }
        printf("%zu\n", ans.size());
        for (auto &v : ans) {
            printf("%d %d\n", v.first, v.second);
        }
    }

    return 0;
}

