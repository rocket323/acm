#include<stdio.h>
int main()
{
	float a[12],b=0;
	int i=0;
	for(i;i<=11;i++) 
	scanf("%f",&a[i]);
	for(;i>=0;i--)
	b=b+a[i];
	printf("$%.2f\n",b/12);
	return 0;
}