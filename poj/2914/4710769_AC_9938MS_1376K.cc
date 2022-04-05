#include <iostream>
#define MaxN 501
#define INF 0x7f7f7f7f
using namespace std;

int N, M, Min;
int g[MaxN][MaxN];
int del[MaxN], w[MaxN];
int in[MaxN];

void init()
{
    memset(g, 0, sizeof g);
    for(int i=1; i<=M; ++i)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a+1][b+1] += c;
        g[b+1][a+1] += c;
    }
}

int findMax()
{
    int Max = -1, rec = -1;
    for(int i=1; i<=N; ++i)
        if(!del[i]&&!in[i]&&w[i]>Max)
        {
            Max = w[i];
            rec = i;
        }
    return rec;
}

void update(int k)
{
    for(int i=1; i<=N; ++i)
        if(!del[i]&&!in[i])
        {
            w[i] += g[i][k];
        }
}

void merge(int s, int t)
{
    del[t] = 1;
    for(int i=1; i<=N; ++i)
    {
        if(del[i]) continue;
        g[s][i] += g[t][i];
        g[i][s] += g[t][i];
    }
}

void go()
{
    int s, t;
    memset(in, 0, sizeof in);
    in[1] = 1;
    s = 1;
    for(int i=2; i<=N; ++i) w[i] = g[i][1];

    for(int x=1; x<N; ++x)
    {
        int k = findMax();
        if(k==-1) break;
        s = t; t = k;
        in[k] = 1;
        update(k);
    }
    merge(s, t);
    if(w[t]<Min) Min = w[t];
}

void solve()
{
    memset(del, 0, sizeof del);
    Min = INF;
    for(int i=1; i<N; ++i)
    {
        go();
    }
    printf("%d\n", Min);
}

int main()
{
    while(scanf("%d%d", &N, &M)!=EOF)
    {
        init();
        solve();
    }
    return 0;
}

