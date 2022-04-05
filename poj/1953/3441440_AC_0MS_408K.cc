#include <iostream>
using namespace std;

int f[46],g[46];

int main(){
	int i,j,k,t=0,n;
	cin>>k;
	for(t=1;t<=k;t++){
		cin>>n;
		f[1]=1; g[1]=1;
		for(i=2;i<=n;i++){
			f[i]=g[i-1];
			g[i]=f[i-1]+g[i-1];
		}
		printf("Scenario #%d:\n",t);
		printf("%d\n\n",f[n]+g[n]);
	}
	return 0;
}
		
