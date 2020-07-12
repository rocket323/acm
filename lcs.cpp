#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

int n;
char s[maxl], t[maxl];
unordered_set<string> st;

bool check(char t[]) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (t[i] == '(')
            cnt++;
        else
            cnt--;

        if (cnt < 0) return false;
    }
    return cnt == 0;
}

int main() {
    scanf("%s", s);
    n = strlen(s);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            int p = 0;
            for (int k = 0; k < j; k++) {
                if (k == i) continue;
                t[p++] = s[k];
            }
            t[p++] = s[i];
            for (int k = j; k < n; k++) {
                if (k == i) continue;
                t[p++] = s[k];
            }
            t[p] = '\0';

            if (check(t)) {
                st.insert(string(t));
            }
        }
    }
    printf("%d\n", (int)st.size() - 1);

    return 0;
}

