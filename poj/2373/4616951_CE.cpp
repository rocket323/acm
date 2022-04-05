#include <iostream>
#define MaxN 1000010
#define INF 1000000000
using namespace std;

struct node
{
    int s, t;
}E[1001];

int A, B, N, L;
bool flag = 1, can[MaxN];
int f[MaxN];

bool cmp(node A, node B){ return A.s<B.s; }

void init()
{
    scanf("%d%d", &N, &L);
    scanf("%d%d", &A, &B);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d%d", &E[i].s, &E[i].t);
        if(E[i].t-E[i].s>2*B) 
        {
            flag = 0;
        }
    }
    sort(E+1, E+1+N, cmp);
    /*for(int i=2; i<=N; ++i)
        if(E[i].s<E[i-1].t)
        {
            flag = 0;
            cout<<"h2"<<endl;
        }*/
}

int Min(int a, int b){ return (a<b)?a:b; }

void solve()
{
    if(!flag)
    {
        printf("-1\n");
        return;
    }
    for(int i=0; i<=L; ++i) can[i] = 1;
    for(int i=1; i<=N; ++i)
        for(int j=E[i].s+1; j<E[i].t; ++j)
            can[j] = 0;

    f[0] = 0;
    for(int i=1; i<=L; ++i)
    {
        f[i] = INF;
        for(int r=A; r<=B; ++r)
        {
            int j=i-2*r;
            if(j>=0&&can[j])
            {
                f[i] = Min(f[i], f[j]+1);
            }
        }
    }
    if(f[L]==INF)
        printf("-1\n");
    else
        printf("%d\n", f[L]);
}

int main()
{
    init();
    solve();
    return 0;
}

