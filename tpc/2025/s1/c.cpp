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
int higher_cnt;

int findone(int i) {
    for (int j = i; j < n; j++) {
        if (higher_cnt <= nd[j].b)
            return j;
    }
    return -1;
}

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
            return l.b < r.b;
        });

        std::vector<int> ans;
        higher_cnt = 0;
        int tmp_a = 0, tmp_cnt = 0;
        for (int i = 0; i < n;) {
            if (tmp_a > 0 && tmp_a != nd[i].a) {
                higher_cnt += tmp_cnt;
                tmp_a = 0;
                tmp_cnt = 0;
            }

            int j = findone(i);
            if (j < 0)
                break;

            int k = findone(j + 1);
            if (k >= 0) {
                if (nd[j].a > nd[k].a && higher_cnt + tmp_cnt + 1 > nd[k].b) {
                    i = k;
                    continue;
                }
            }

            ans.push_back(nd[j].idx);
            if (tmp_a == nd[j].a) {
                tmp_cnt++;
            } else {
                higher_cnt += tmp_cnt;
                tmp_a = nd[j].a;
                tmp_cnt = 1;
            }

            i = j + 1;
        }
        sort(ans.begin(), ans.end());
        printf("%d\n", (int)ans.size());
        for (int i = 0; i < ans.size(); i++) {
            printf("%d%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
        }
    }
    return 0;
}
