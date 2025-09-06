#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

struct node {
    int a, b, idx;
} nd[maxl];

int t, n;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &nd[i].a, &nd[i].b);
            nd[i].idx = i + 1;
        }

        sort(nd, nd + n, [](const node &l, const node &r) {
            if (l.a != r.a)
                return l.a > r.a;
            return l.b > r.b;
        });

        std::vector<int> ans;
        int i = 0;
        while (i < n) {
            int j = i, idx = -1, num = -1;
            while (j < n && nd[j].a == nd[i].a) {
                int tmp = (j - i + 1) + min((int)ans.size(), nd[j].b);
                if (tmp > num) {
                    idx = j;
                    num = tmp;
                }
                j++;
            }
            if (num > ans.size()) {
                int b = nd[idx].b;
                while (ans.size() > b)
                    ans.pop_back();
                for (int x = i; x <= idx; x++)
                    ans.push_back(nd[x].idx);
            }
            i = j;
        }
        sort(ans.begin(), ans.end());
        printf("%d\n", (int)ans.size());
        for (int i = 0; i < ans.size(); i++) {
            printf("%d%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
        }
    }
    return 0;
}
