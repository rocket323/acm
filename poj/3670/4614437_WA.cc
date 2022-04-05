#include <iostream>
#define MaxN 305
#define INF 1000000000
using namespace std;

struct node
{
    int r, c, dis;
}H[200000];

int arr[MaxN][MaxN], des[MaxN][MaxN];
int M;
int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};
int d[MaxN][MaxN];
int vis[MaxN][MaxN], len = 0;

void init()
{
    int a, b, t;
    scanf("%d", &M);
    
    for(int i=0; i<MaxN; ++i)
        for(int j=0; j<MaxN; ++j)
        {
            arr[i][j] = des[i][j] = INF;
        }

    for(int i=1; i<=M; ++i)
    {
        scanf("%d%d%d", &a, &b, &t);
        if(arr[a][b]>t) des[a][b] = arr[a][b] = t;
    }
    for(int i=0; i<MaxN; ++i)
        for(int j=0; j<MaxN; ++j)
        {
            for(int k=0; k<4; ++k)
            {
                int ii=i+dr[k], jj=j+dc[k];
                if(ii>=0&&ii<MaxN&&jj>=0&&jj<MaxN)
                {
                    if(arr[ii][jj]<des[i][j])
                        des[i][j] = arr[ii][jj];
                }
            }
        }
}

void swap(int a, int b)
{
    node tmp;
    tmp=H[a]; H[a]=H[b]; H[b]=tmp;
}

node pop(){
	int i,j,k,t;
    node res;
    res.r=-1;
	
	if(len==0) return res;
	
	res.r=H[1].r;
    res.c=H[1].c;
    res.dis=H[1].dis;
    swap(1, len);
	len--;
	k=1;
	while(k<len){
		i=k<<1; j=i+1;
		if(i>len) break;
		if(j>len) t=i;
		else{
			if(H[i].dis<H[j].dis) t=i;
			else t=j;
		}
		if(H[t].dis<H[k].dis){
			swap(t, k);
			k=t;
		}
		else break;
	}
	return res;
}

void push(int r, int c, int dis)
{
    int i,j,k, mid;
    len++;
    H[len].r=r; H[len].c=c; H[len].dis=dis;
    k=len;
    while(k>1)
    {
        mid=k>>1;
        if(H[k].dis<H[mid].dis)
        {
            swap(k, mid);
            k=mid;
        }
        else break;
    }
}

void shortest_path()
{
    for(int i=0; i<MaxN; ++i)
        for(int j=0; j<MaxN; ++j)
            d[i][j] = INF;
    d[0][0] = 0;
    memset(vis, 0, sizeof vis);
    push(0, 0, 0);

    node rec;
    for(int x=1; x<MaxN*MaxN; ++x)
    {
        while(true)
        {
            rec = pop();
            if(rec.r==-1) break;
            if(!vis[rec.r][rec.c]) break;
        }

        if(rec.r==-1) break;
        vis[rec.r][rec.c] = 1;

        for(int k=0; k<4; ++k)
        {
            int ii=rec.r+dr[k];
            int jj=rec.c+dc[k];
            if(ii<0||ii>=MaxN||jj<0||jj>=MaxN) continue;
            if(d[rec.r][rec.c]+1<des[ii][jj]&&d[rec.r][rec.c]+1<d[ii][jj])
            {
                d[ii][jj] = d[rec.r][rec.c]+1;
                push(ii, jj, d[ii][jj]);
            }
        }
    }
}

void solve()
{
    int res = -1, Min = INF;
    shortest_path();

    for(int i=0; i<MaxN; ++i)
        for(int j=0; j<MaxN; ++j)
            if(des[i][j]==INF&&d[i][j]<Min)
            {
                Min = d[i][j];
                res = Min;
            }
    printf("%d\n", res);
}

int main()
{
    init();
    solve();
    return 0;
}

