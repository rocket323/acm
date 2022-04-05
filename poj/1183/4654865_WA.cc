#include <stdio.h>

int main()
{
    long long n, a, res;
    scanf("%I64d", &a);
    n = 4*(a*a+1);
    for(long long i=n; i*i>=n; --i)
    {
        if(n%i) continue;
        long long j=n/i;
        if((i+j)%2!=0) continue;
        res = (i+j)/2;
        break;
    }
    printf("%I64d\n", res + 2*a);
    return 0;
}

