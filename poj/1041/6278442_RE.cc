#include <stdio.h>
#include <cstring>
#include <vector>
#define maxl 100
using namespace std;

char str[100];
int n, m, sz, list[maxl], a, b, d[maxl], c;
vector<int> e[maxl][maxl];
int g[maxl][maxl];
int ans[maxl], top;

void dfs(int now)
{
    for(int i=0; i<sz; ++i)
    {
        if(g[now][list[i]] > 0)
        {
            g[now][list[i]]--;
            g[list[i]][now]--;
            dfs(list[i]);
        }
    }
    ans[top++] = now;
}

void out(int a, int b, int c)
{
    if(a > b){ a ^= b; b ^= a; a ^= b; }

    printf("%d%c", e[a][b].back(), c);
    e[a][b].pop_back();
}

void solve()
{
    for(int i=0; i<sz; ++i) if(d[i] & 1)
    {
        puts("Round trip does not exist.");
        return;
    }

    top = 0;
    dfs(list[0]);

    for(int i=top-1; i>1; --i)
    {
        out(ans[i], ans[i-1], ' ');
    }
    out(ans[1], ans[0], '\n');
}

void add(int a)
{
    for(int i=0; i<sz; ++i) if(list[i] == a) return;
    list[sz++] = a;
}

int main()
{
    while(true)
    {
        m = sz = 0;
        memset(d, 0, sizeof d);
        memset(g, 0, sizeof g);
        while(gets(str))
        {
            if(sscanf(str, "%d%d%d", &a, &b, &c) != 3) break;
            m++;
            add(a), add(b);
            d[a]++; d[b]++;
            g[a][b]++; g[b][a]++;

            if(a <= b) e[a][b].push_back(c);
            else e[b][a].push_back(c);
        }
        if(!m) break;
        solve();
    }
    return 0;
}

