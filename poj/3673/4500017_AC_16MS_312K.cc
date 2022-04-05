#include <stdio.h>

void process(int a, int b)
{
    int sum = 0;
    int aa=a, bb=b;
    while(aa)
    {
        bb=b;
        int n1 = aa%10;
        while(bb)
        {
            int n2 = bb%10;
            sum += (n1*n2);
            bb /= 10;
        }
        aa /= 10;
    }
    printf("%d\n", sum);
}

int main()
{
    int a, b;
    while(scanf("%d%d", &a, &b)!=EOF)
    {
        process(a, b);
    }
    return 0;
}
