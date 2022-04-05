#include <iostream>
using namespace std;

int G[6][6];
int cnt;
int vis[6][6];
int qc[26], qr[26], head, tail;
int lv[6][6];
int dr[4] = {0, -1, 0, 1};
int dc[4] = {1, 0, -1, 0};
int L[26], R[26], start;

void init()
{
    char ch;
    for(int i=1; i<=5; ++i)
    {
        for(int j=1; j<=5; ++j)
        {
            scanf("%c", &ch);
            if(ch=='H')
                G[i][j] = 0;
            else G[i][j] = 1;
        }
        scanf("\n");
    }
}

int check()
{
    int i,j,k, ct = 0;
    for(i=1; i<=5; ++i)
    {
        for(j=1; j<=5; ++j)
            if(vis[i][j])
                break;
        if(vis[i][j]) break;
    }

    memset(lv, 0, sizeof lv);
    head = tail = 1;
    qr[1]=i; qc[1]=j;
    lv[i][j] = 1;
    ++ct;

    while(head<=tail)
    {
        for(k=0; k<4; ++k)
        {
            int ii=qr[head]+dr[k];
            int jj=qc[head]+dc[k];
            if(vis[ii][jj]&&!lv[ii][jj])
            {
                lv[ii][jj] = 1;
                ++tail;
                qr[tail] = ii;
                qc[tail] = jj;
                ++ct;
            }
        }
        head++;
    }
    if(ct==7) return 1;
    else return 0;
}

void dfs(int sum, int w, int st)
{
    if(sum-w>3) return;
    
    if(sum==7)
    {
        if(w>3&&check()) ++cnt;
        return;
    }

    for(int k=st; k<=25; ++k)
    {
        int j = k%5;
        if(j==0) j=5;
        int i = (k-j)/5 + 1;
        if(!vis[i][j])
        {
            vis[i][j] = 1;
            dfs(sum+1, w+G[i][j], k+1);
            vis[i][j] = 0;
        }
    }
}

void process()
{
    memset(vis, 0, sizeof vis);
    dfs(0, 0, 1);
    printf("%d\n", cnt);
}

int main()
{
    init();
    process();
    return 0;
}

