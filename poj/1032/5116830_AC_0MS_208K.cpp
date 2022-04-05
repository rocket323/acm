#include <stdio.h>

int a[1001], tp = 0;

int main()
{
	int b = 1, n, sum = 0;
	scanf("%d", &n);
	while(n >= b+1)
	{
		a[tp++] = ++b;
		n -= b;
	}
	int k = tp-1;
	while(n)
	{
		a[k]++;
		n--;
		k = (k + tp -1) % tp;
	}
	for(int i=0; i<tp-1; ++i) printf("%d ", a[i]);
	printf("%d\n", a[tp-1]);
}