#include <iostream>
#include <algorithm>
#include <sstream>
#define MaxL 100010
using namespace std;

struct node
{
    char a[11];
    char b[11];
}A[MaxL];

int N;

bool cmp(node A, node B){ return strcmp(A.a, B.a)<0; }

int find(char a[])
{
    int l=1, r=N;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        int k = strcmp(a, A[mid].a);
        if(k==0) return mid;
        if(k>0)
            l=mid+1;
        else
            r=mid-1;
    }
    return -1;
}

void process()
{
    char S[100], s1[11], s2[11];
    gets(S);
    N = 0;
    while(S[0])
    {
        sscanf(S, "%s%s", s1, s2);
        ++N;
        strcpy(A[N].a, s2);
        strcpy(A[N].b, s1);
        gets(S);
    }
    sort(A+1, A+N+1, cmp);
    
    while(gets(S))
    {
        int k=find(S);
        if(k!=-1)
            printf("%s\n", A[k].b);
        else
            printf("eh\n");
    }
}

int main()
{
    process();
    return 0;
}

