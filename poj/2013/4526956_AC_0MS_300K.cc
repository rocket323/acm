#include <stdio.h>
#include <cstring>

int N;
char S[100][100];
char T[100][100];

void init()
{
    for(int i=1; i<=N; ++i)
    {
        gets(S[i]);
    }
}

void process(int ca)
{
    printf("SET %d\n", ca);
    int l=1, r=N;
    for(int i=1; i<=N; i+=2)
    {
        if(i<N)
        {
            strcpy(T[l], S[i]);
            strcpy(T[r], S[i+1]);
        }
        else
        {
            strcpy(T[l], S[i]);
        }
        l++; r--;
    }

    for(int i=1; i<=N; ++i)
    {
        printf("%s\n", T[i]);
    }
}

int main()
{
    int K = 0;
    //freopen("2013.in", "r", stdin);
    scanf("%d\n", &N);
    while(N!=0)
    {
        init();
        process(++K);
        scanf("%d\n", &N);
    }
    return 0;
}
