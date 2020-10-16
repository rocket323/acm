#include <bits/stdc++.h>

int n;
std::string s[100][100];
int a[100];
std::unordered_map<char, int> mp;

void out(int a[]) {
    for (int i = 1; i < n; i++) {
        printf("%d ", a[i]);
    }
    puts("");
}

int calc(const std::string &s) {
    int m = n - 1;
    int ans = 0;
    for (int i = 0; i < s.length(); i++) {
        ans = ans * m + a[mp[s[i]]];
    }
    return ans;
}

bool check() {
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            int c = a[i] + a[j];
            int d = calc(s[i][j]);
            if (c != d)
                return false;
        }
    }

    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char t[10];
            scanf("%s", t);
            s[i][j] = t;
        }
    }

    for (int i = 1; i < n; i++) {
        a[i] = i - 1;
        char ch = s[0][i][0];
        mp[ch] = i;
    }

    do {
        if (check()) {
            for (int i = 1; i < n; i++) {
                if (i > 1)
                    printf(" ");
                printf("%s=%d", s[0][i].c_str(), a[i]);
            }
            printf("\n%d\n", n - 1);
            return 0;
        }
    } while (std::next_permutation(a + 1, a + n));

    puts("ERROR!");

    return 0;
}
