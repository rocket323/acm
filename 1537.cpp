#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int maxn = 1007;

int n;
int a[maxn];

int maxDec[maxn];
int pos[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        maxDec[i] = 1;
        pos[i] = i;
    }

    int maxRem = 0;

    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (a[i] > a[j]) {
                maxDec[i] = max(maxDec[i], maxDec[j] + 1);
                maxRem = max(maxRem, maxDec[i]);
            }
        }
    }

    sort(pos, pos + n, [](const int &x, const int &y) -> bool {
            return a[x] > a[y];
            });

    int left = pos[0], right = pos[0];
    int k;
    for (k = 1; k < n; k++) {
        if (pos[k] > left && pos[k] < right) {
            maxRem = max(maxRem, k + maxDec[right] - 1);
            break;
        } else {
            left = min(left, pos[k]);
            right = max(right, pos[k]);
        }
    }
    if (k == n) {
        maxRem = n;
    }

    printf("%d\n", n - maxRem);

    return 0;

}
