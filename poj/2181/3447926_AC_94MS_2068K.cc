#include <iostream>
using namespace std;

int n,a[150001],f1[150001],f2[150001];

int Max(int u, int v){
	return (u>v)?u:v;
}

int main(){
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	f1[1]=a[1]; f2[1]=0;
	for(i=2;i<=n;i++){
		f1[i]=Max(f1[i-1], f2[i-1]+a[i]);
		f2[i]=Max(f1[i-1]-a[i], f2[i-1]);
	}
	printf("%d\n",Max(f1[n], f2[n]));
	return 0;
}
