#include <iostream>
#define MS 50
#define sz (1<<m)
using namespace std;

int n, m, mod;
int A[MS][MS];
int B[MS][MS];
int I[MS][MS];

void dfs(int s, int pos, int t)
{
    if(pos==m)
    {
        A[s][t] = 1;
        return;
    }
    if(s&(1<<pos)) dfs(s, pos+1, t);
    else
    {
        int tmp = t;
        dfs(s, pos+1, (t | (1<<pos)) );
        if(pos<m-1 && !(s&(1<<(pos+1)))) dfs(s, pos+2, t);
    }
}

void init()
{
    m = 4;
    memset(A, 0, sizeof A);
    for(int i=0; i<sz; ++i)
    {
        dfs(i, 0, 0);
    }
}

void matrix(int C[][MS], int A[][MS], int B[][MS])
{
    for(int i=0; i<sz; ++i)
    {
        for(int j=0; j<sz; ++j)
        {
            C[i][j] = 0;
            for(int k=0; k<sz; ++k)
            {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
            }
        }
    }
}

void pow(int n, int B[][MS])
{
    if(n==0)
    {
        memcpy(B, I, sizeof I);
        return;
    }
    pow(n/2, B);

    int tmp[MS][MS];
    matrix(tmp, B, B);
    
    if(n&1) matrix(B, tmp, A);
    else matrix(B, tmp, I);
}

void solve()
{

    memset(I, 0, sizeof I);
    for(int i=0; i<sz; ++i) I[i][i] = 1;

    pow(n, B);
    printf("%d\n", B[0][0]);
}

int main()
{
    while(scanf("%d%d", &n, &mod) && mod)
    {
        init();
        solve();
    }
    return 0;
}

