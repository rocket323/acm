#include <iostream>
using namespace std;

int w[4000],d[4000],f[20000];

int Max(int a, int b){
	return (a>b)?a:b;
}

int main(){
	int i,j,k,n,m;
//	freopen("3624.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		scanf("%d%d",&w[i],&d[i]);
	memset(f,0,sizeof f);
	for(i=1;i<=n;i++)
		for(j=m;j>=w[i];j--)
			f[j]=Max(f[j],f[j-w[i]]+d[i]);
	printf("%d\n",f[m]);
//	while(k=1);
	return 0;
}
