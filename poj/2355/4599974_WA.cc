#include <iostream>
#define MaxN 10010
#define INF 1000000000
using namespace std;

int l1, l2, l3, c1, c2, c3, S, T, N;
int P[MaxN];
int A[MaxN], B[MaxN], f[MaxN];
int head, tail;

void init()
{
    scanf("%d%d%d%d%d%d", &l1,&l2,&l3,&c1,&c2,&c3);
    scanf("%d", &N);
    scanf("%d%d", &S, &T);
    P[1] = 0;
    for(int i=2; i<=N; ++i)
        scanf("%d", &P[i]);
    if(S>T)
    {
        int tmp = S; S = T; T = tmp;
    }
}

int getPrice(int a, int b)
{
    int t = P[b]-P[a];
    if(t>0&&t<l1) return c1;
    if(t<=l2) return c2;
    if(t<=l3) return c3;
    return INF;
}

void countTheF(int x)
{
    while( head<tail-1 && B[A[head+1]]<=x )
    {
        head++;
    }
    f[x] = f[A[head]] + getPrice(A[head], x);
    //cout<<x<<' '<<A[head]<<' '<<f[x]<<endl;
}

int getY(int a, int b, int c)
{
    int l, r, mid, res = INF;
    l = a+1; r = T;
    while(l<=r)
    {
        int mid = (l+r)>>1;
        int w = getPrice(a, mid)-getPrice(b, mid);
        if(w<=c)
        {
            res = mid;
            r = mid-1;
        }
        else l = mid+1;
    }
    return res;
}

void insert(int x)
{
    int y;
    while(head<tail)
    {
        y = getY(x, A[tail-1], f[A[tail-1]]-f[x]);
        if(y<=B[A[tail-1]])
            --tail;
        else break;
    }
    A[tail] = x;
    B[x] = y;
    ++tail;
}

void solve()
{
    f[S] = 0;
    A[head = 1] = S;
    B[S] = S+1;
    tail = 2;
    
    for(int i=S+1; i<=T; ++i)
    {
        countTheF(i);
        if(i<T) insert(i);
    }
    printf("%d\n", f[T]);
}

int main()
{
    //freopen("2355.in", "r", stdin);
    init();
    solve();
    return 0;
}

