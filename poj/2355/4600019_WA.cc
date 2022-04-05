#include <iostream>
#define MaxN 10010
#define INF 1000000000
using namespace std;

long long l1, l2, l3, c1, c2, c3, S, T, N;
long long P[MaxN];
long long A[MaxN], B[MaxN], f[MaxN];
long long head, tail;

void init()
{
    scanf("%I64d%I64d%I64d%I64d%I64d%I64d", &l1,&l2,&l3,&c1,&c2,&c3);
    scanf("%I64d", &N);
    scanf("%I64d%I64d", &S, &T);
    P[1] = 0;
    for(long long i=2; i<=N; ++i)
        scanf("%I64d", &P[i]);
    if(S>T)
    {
        long long tmp = S; S = T; T = tmp;
    }
}

long long getPrice(long long a, long long b)
{
    long long t = P[b]-P[a];
    if(t>0&&t<l1) return c1;
    if(t<=l2) return c2;
    if(t<=l3) return c3;
    return INF;
}

void countTheF(long long x)
{
    while( head<tail-1 && B[A[head+1]]<=x )
    {
        head++;
    }
    f[x] = f[A[head]] + getPrice(A[head], x);
    //cout<<x<<' '<<A[head]<<' '<<f[x]<<endl;
}

long long getY(long long a, long long b, long long c)
{
    long long l, r, mid, res = INF;
    l = a+1; r = T;
    while(l<=r)
    {
        long long mid = (l+r)>>1;
        long long w = getPrice(a, mid)-getPrice(b, mid);
        if(w<=c)
        {
            res = mid;
            r = mid-1;
        }
        else l = mid+1;
    }
    return res;
}

void insert(long long x)
{
    long long y;
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
    
    for(long long i=S+1; i<=T; ++i)
    {
        countTheF(i);
        if(i<T) insert(i);
    }
    cout<<f[T]<<endl;
    //printf("%I64d\n", f[T]);
}

int main()
{
    //freopen("2355.in", "r", stdin);
    init();
    solve();
    return 0;
}

