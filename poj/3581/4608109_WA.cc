#include <iostream>
#include <algorithm>
#define MaxN 200010
using namespace std;

int N;
int A[MaxN], S[MaxN], tmp[MaxN];
int list[MaxN], b[MaxN], rank[MaxN], head[MaxN], next[MaxN];
int res[MaxN], top;

void init()
{
    for(int i=0; i<N; ++i)
        scanf("%d", &A[i]);
    for(int i=0; i<N; ++i)
        S[i] = A[N-1-i];
}

bool cmp(int i, int j){ return tmp[i]<tmp[j]; }

int suffix_sort(int s, int t, int N)
{
    int i,j,k, h;

    for(i=0; i<N; ++i) tmp[i] = S[i+s];

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

    return list[0]+s;

    /*for(i=list[0]; i<N; ++i)
        cout<<S[i]<<' ';
    cout<<endl;*/

}

void solve()
{
    int k1, k2;
    top = 0;
    k1   = suffix_sort(2, N-1, N-2);
    for(int i=k1; i<N; ++i) res[++top] = S[i];

    k2 = suffix_sort(1, k1-1, k1-1);

    for(int i=k2; i<k1; ++i) res[++top] = S[i];
    for(int i=0; i<k2; ++i) res[++top] = S[i];

    for(int i=1; i<=top; ++i)
        printf("%d\n", res[i]);
}

int main()
{
    //freopen("3581.in", "r", stdin);
    scanf("%d", &N);
    init();
    solve();
    return 0;
}

