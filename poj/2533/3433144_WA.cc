#include <iostream>
using namespace std;

int n,f[1001],a[1001];

int main(){
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	f[1]=1;
	for(i=2;i<=n;i++){
		f[i]=1;
		for(j=1;j<i;j++)
			if(a[j]<=a[i]&&f[j]+1>f[i])
				f[i]=f[j]+1;
	}
	printf("%d\n",f[n]);
	return 0;
}
