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

const double inf = 1e15;
const int maxl = 2e5 + 10;
const double eps = 1e-8;

double D1, C, D2, P, d[maxl], p[maxl], ans;
int N;

void dfs(int now, double oil, double cur_cost) {
    if (now == N - 1) {
        ans = min(ans, cur_cost);
        return;
    }
    for (int i = now + 1; i < N; i++) {
        double cost = (d[i] - d[now]) / D2;
        if (cost > C + eps)
            continue;

        // 加最少的油
        if (oil >= cost)
            dfs(i, oil - cost, cur_cost);
        else
            dfs(i, 0, cur_cost + (cost - oil) * p[now]);

        // 加满油
        dfs(i, C - cost, cur_cost + (C - oil) * p[now]);
    }
}

int main() {
    cin >> D1 >> C >> D2 >> P >> N;
    d[0] = 0;
    p[0] = P;
    d[N + 1] = D1;
    p[N + 1] = 1;
    for (int i = 1; i <= N; i++) {
        cin >> d[i] >> p[i];
    }
    N += 2;
    ans = inf;
    dfs(0, 0, 0);
    if (ans < inf - 2)
        printf("%.2lf\n", ans);
    else
        puts("No Solution");
    return 0;
}