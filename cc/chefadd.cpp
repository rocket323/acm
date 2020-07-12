#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

int a, b, c, t, n;
int as[50], bs[50], cs[50];
int f[50][35][35][2];
int ac, bc, cc;

void calc(int n, int arr[], int &len, int &cnt) {
    // printf("%d: ", n);
    len = 0;
    cnt = 0;
    for (int i = 0; i <= 31; i++) {
        if (n & (1 << i)) {
            arr[i + 1] = 1;
            len = i + 1;
            cnt++;
        } else {
            arr[i + 1] = 0;
        }
        // printf("%d ", arr[i]);
    }
    // puts("");
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &a, &b, &c);

        calc(a, as, n, ac);
        calc(b, bs, n, bc);
        calc(c, cs, n, cc);
        // printf("x %d %d %d\n", n, ac, bc);

        memset(f, 0, sizeof f);
        f[0][0][0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= ac; j++) {
                for (int k = 0; k <= bc; k++) {
                    for (int p = 0; p < 2; p++) {
                        if (f[i][j][k][p] == 0) continue;

                        for (int jj = 0; jj < 2; jj++) {
                            for (int kk = 0; kk < 2; kk++) {
                                int v = jj + kk + p;
                                if (v % 2 != cs[i + 1]) continue;

                                if (j + jj <= ac && k + kk <= bc) {
                                    f[i + 1][j + jj][k + kk][v / 2] += f[i][j][k][p];
                                }
                            }
                        }
                    }
                }
            }
        }

        printf("%d\n", f[n][ac][bc][0]);
    }

    return 0;
}

