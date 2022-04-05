#include <iostream>
#define Max 100000000
using namespace std;

int n,s,c[10001],y[10001],sum,Min;

int main(){
	int i,j,k;
	scanf("%d%d",&n,&s);
	sum=0;
	for(i=1;i<=n;i++){
		scanf("%d%d",&c[i],&y[i]);
		if(i==1)
			sum+=c[i]*y[i];
		else{
			Min=c[i]*y[i];
			for(j=1;j<i;j++)
				if(c[j]*y[i]+s*y[i]*(i-j)<Min)
					Min=c[j]*y[i]+s*y[i]*(i-j);
			sum+=Min;
		}
	}
	printf("%d\n",sum);
	return 0;
}
