#include <iostream>
#include <algorithm>
#define MaxN 400010
#define INF 2000000000
using namespace std;

int N;
int A[MaxN], S[MaxN], tmp[MaxN], cnt[MaxN];
int list[MaxN], b[MaxN], rank[MaxN], head[MaxN], next[MaxN];
int res[MaxN], top;

void init()
{
    int t = 0;
    for(int i=0; i<N; ++i)
        scanf("%d", &A[i]);
    for(int i=0; i<N; ++i)
        S[i] = A[N-1-i];
}

bool cmp(int i, int j){ return tmp[i]<tmp[j]; }

int suffix_sort(int N)
{
    int i,j,k, h;

    for(i=0; i<N; ++i) list[i] = i;
    sort(list, list+N, cmp);

    b[list[0]] = 0;
    for(i=1; i<N; ++i)
        if(tmp[list[i]]==tmp[list[i-1]]) b[list[i]] = b[list[i-1]];
        else b[list[i]] = i;

    for(h=1; h<N; h<<=1)
    {
        for(i=0; i<N; ++i) head[i] = next[i] = -1;
        for(i=N-1; i>=0; --i)
            if(list[i]!=0)
            {
                j=list[i]-h; if(j<0) j += N;
                next[j] = head[b[j]];
                head[b[j]] = j;
            }
        j=N-h; next[j]=head[b[j]]; head[b[j]]=j;
        for(i=k=0; i<N; ++i)
            if(head[i]>=0)
                for(j=head[i]; j>=0; j=next[j])
                    list[k++]=j;
        for(i=0; i<N; ++i)
            if(i>0&&list[i]+h<N&&list[i-1]+h<N&&b[list[i]]==b[list[i-1]]&&b[list[i]+h]==b[list[i-1]+h])
                rank[list[i]] = rank[list[i-1]];
            else rank[list[i]] = i;
        for(i=0; i<N; ++i) b[i] = rank[i];
    }


    return list[0];

}

void solve()
{
    int k1, k2, pos = -1, Min = INF;
    top = 0;
    for(int i=2; i<N; ++i) tmp[i-2] = S[i];
    k1   = suffix_sort(N-2) + 2;
    for(int i=k1; i<N; ++i) res[++top] = S[i];

    for(int i=1; i<k1; ++i)
        tmp[i-1] = S[i];
    for(int i=0; i<k1; ++i)
        tmp[i+k1-1] = S[i];

    k2 = suffix_sort(2*k1-1);

    Min = INF;
    for(int i=0; i<=k1-2; ++i)
        if(rank[i]<Min)
        {
            Min = rank[i];
            pos = i;
        }
    
    for(int i=pos; i<pos+k1; ++i)
        res[++top] = tmp[i];


    for(int i=1; i<=top; ++i)
        printf("%d\n", res[i]);
}

int main()
{
    scanf("%d", &N);
    init();
    solve();
    return 0;
}

