#include <iostream>
#include <algorithm>
#define MaxN 200010
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
    int i = N-1;
    
    while(i>=0)
    {
        S[t++] = A[i--];
        cnt[t-1] = 1;
        while(A[i]==S[t-1]&&i>=0)
        {
            ++cnt[t-1];
            --i;
        }
    }
    N = t;
}

bool cmp(int i, int j){ return tmp[i]<tmp[j]||(tmp[i]==tmp[j]&&i<j); }

int suffix_sort(int s, int t, int N)
{
    int i,j,k, h;

    for(i=0; i<N-1; ++i) tmp[i] = S[i+s];
    tmp[N-1] = -INF;

    for(i=0; i<N; ++i) list[i] = i;
    sort(list, list+N, cmp);


    /*cout<<" H ";
    for(int i=0; i<N; ++i) cout<<list[i]<<' ';
    cout<<endl;*/

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

    /*for(i=0; i<N; ++i)cout<<list[i]<<' ';
    cout<<endl;*/

    return list[1]+s;

    /*for(i=list[0]; i<N; ++i)
        cout<<S[i]<<' ';
    cout<<endl;*/

}

void solve()
{
    int k1, k2;
    top = 0;
    k1   = suffix_sort(2, N-1, N-1);
    for(int i=k1; i<N; ++i)
        for(int j=1; j<=cnt[i]; ++j)
            res[++top] = S[i];

    k2 = suffix_sort(1, k1-1, k1);

    for(int i=k2; i<k1; ++i)
        for(int j=1; j<=cnt[i]; ++j)
            res[++top] = S[i];
    for(int i=0; i<k2; ++i)
        for(int j=1; j<=cnt[i]; ++j)
            res[++top] = S[i];

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

