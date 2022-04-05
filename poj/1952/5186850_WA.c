#include <stdio.h>
long L[5003]={0},N[5003]={0},a[5003];
int main()
{
	long n,i,j,max,flag,sum;
	scanf("%ld",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%ld",&a[i]);
		for(j=i-1,flag=0;j>=1;j--)
		{
			if(a[j]==a[i]&&L[j]>=L[i])
			{
				if(flag==0)
				{
					L[i]=0;
					N[i]=0;
					flag=1;
				}
				break;
			}
			else if(a[j]>a[i])
			{
				if(flag==1)
				{
					if(L[j]+1==L[i])
						N[i]+=N[j];
					else if(L[j]+1>L[i])
					{
						L[i]=L[j]+1;
						N[i]=N[j];
					}
				}
				else
				{
					flag=1;
					L[i]=L[j]+1;
					N[i]=N[j];
				}
			}
		}
		if(flag==0)
		{
			N[i]=1;
			L[i]=1;
		}
		if(L[i]>max)
		{
			max=L[i];
		}
	}
	for(sum=0,i=1;i<=n;i++)
	{
		if(L[i]==max)
			sum+=N[i];
	}
	printf("%ld %ld\n",max,sum);
	return 0;
}