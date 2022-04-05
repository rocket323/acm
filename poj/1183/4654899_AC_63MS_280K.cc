#include <stdio.h>
#define ll long long

int main()
{
    long long n, a, res=(ll)1000000*(ll)1000000;
    scanf("%I64d", &a);
    n = 4*((ll)a*(ll)a+1);
    long long k = 2*a+10;
    for(long long i=1; i<=k; ++i)
    {
        if(n%i) continue;
        long long j=n/i;
        if((i+j)%2!=0) continue;
        if((i+j)/2<res)
            res = (i+j)/2;
    }
    printf("%I64d\n", res + 2*a);
    return 0;
}

