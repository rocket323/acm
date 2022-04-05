#include <iostream>
using namespace std;

char S[1000000];

int getID(char ch)
{
    if(ch>='0'&&ch<='9') return ch-'0';
    if(ch>='A'&&ch<='Z') return ch-'A'+10;
    if(ch>='a'&&ch<='z') return ch-'a'+36;
}

void solve()
{
    int sum = 0, mx = 0;
    for(int i=0; i<strlen(S); ++i)
    {
        int k = getID(S[i]);
        if(k>mx) mx = k;
        sum += k;
    }
    if(mx<2) mx=2;
    for(int N=mx+1; N<=62; ++N)
        if(sum%(N-1)==0)
        {
            printf("%d\n", N);
            return;
        }
    printf("such number is impossible!\n");
}

int main()
{
    while(gets(S))
        solve();
    return 0;
}

