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
#include <unordered_map>
using namespace std;

typedef long long ll;
const int maxl = 1000010;
const int mod = 1e9 + 7;

int n, a[20];
unordered_map<string, int> cnts;

void gao() {
    for (int i = 1; i <= n; i++)
        a[i] = i;

    for (int i = 1; i <=n; i++) {
        int j = rand() % n + 1;
        swap(a[i], a[j]);
    }

    string str;
    for (int i = 1; i <= n; i++) {
        str += to_string(a[i]);
        if (i < n)
            str += " ";
    }

    cnts[str]++;
}

int main() {
    srand(time(0));

    while (scanf("%d", &n) != EOF) {
        cnts.clear();
        for (int i = 0; i < maxl; i++) {
            gao();
        }

        int max_cnt = -1, min_cnt = -1;
        string max_str, min_str;
        for (auto &kv : cnts) {
            if (max_cnt == -1 || kv.second > max_cnt) {
                max_cnt = kv.second;
                max_str = kv.first;
            }

            if (min_cnt == -1 || kv.second < min_cnt) {
                min_cnt = kv.second;
                min_str = kv.first;
            }
        }
        printf("%s\n", max_str.c_str());
        printf("%s\n", min_str.c_str());
    }

    return 0;
}

