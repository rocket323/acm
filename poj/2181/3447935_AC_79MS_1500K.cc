#include <iostream>
using namespace std;

int n,f1[150001],f2[150001];

int Max(int u, int v){
	return (u>v)?u:v;
}

int main(){
	int i,j,k,a;
	scanf("%d",&n);
	scanf("%d",&a);
	f1[1]=a; f2[1]=0;
	for(i=2;i<=n;i++){
		scanf("%d",&a);
		f1[i]=Max(f1[i-1], f2[i-1]+a);
		f2[i]=Max(f1[i-1]-a, f2[i-1]);
	}
	printf("%d\n",Max(f1[n], f2[n]));
	return 0;
}
