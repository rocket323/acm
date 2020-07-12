#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

int c[11];
int vis[100];
char s[maxl];

void go(int i, int j) {
    int num = i * 10 + j;
    vis[num] = 1;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        memset(c, 0, sizeof c);
        memset(vis, 0, sizeof vis);
        for (int i = 0; s[i]; ++i)
            c[s[i] - '0']++;
        
        for (int i = 0; i <= 10; ++i) {
            if (!c[i]) continue;
            for (int j = 0; j <= 10; ++j) {
                if (!c[j]) continue;
                if (i != j) {
                    go(i, j);
                    go(j, i);
                } else if (c[i] > 1) {
                    go(i, i);
                }
            }
        }
        for (int i = 65; i <= 90; ++i) {
            if (vis[i]) printf("%c", 'A' + i - 65);
        }
        puts("");
    }

    return 0;
}


