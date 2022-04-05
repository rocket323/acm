#include <iostream>
using namespace std;

int n,s,c[10001],y[10001],Min[10001];
long long sum=0;

int main(){
	int i,j,k;
	scanf("%d%d",&n,&s);
	sum=0;
	for(i=1;i<=n;i++){
		scanf("%d%d",&c[i],&y[i]);
		if(i==1)
			Min[i]=c[i];
		else{
			Min[i]=c[i];
			for(j=1;j<i;j++)
				if(c[j]+s*(i-j)<Min[i])
					Min[i]=c[j]+s*(i-j);
			
		}
	}
	for(i=1;i<=n;i++) sum+=Min[i]*y[i];
	cout<<sum<<endl;
	return 0;
}
