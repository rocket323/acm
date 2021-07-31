#include <stdio.h>
#include <cstring>
#include <vector>
using namespace std;

const int maxl = 1e5 + 10;
int t, n;

vector<int> a, b;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        a.clear();
        b.clear();
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            if (i & 1)
                b.push_back(x);
            else
                a.push_back(x);
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        bool ch = true;
        for (int i = 0; i < b.size(); i++) {
            if (b[i] < a[i]) {
                ch = false;
            }
            if (i + 1 < a.size() && b[i] > a[i+1]) {
                ch = false;
            }
        }
        puts(ch || n % 2 == 1 ? "Yes" : "No");
    }
    return 0;
}
