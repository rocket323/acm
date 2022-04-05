#include <iostream>
using namespace std;

double a[1001];
int n;
int f[1001],g[1001];

void process(){
	int i,j,k,ans=0;
	f[1]=1;
	for(i=2;i<=n;i++){
		f[i]=1;
		for(j=1;j<i;j++)
			if(a[j]<a[i]&&f[j]+1>f[i])
				f[i]=f[j]+1;
	}
	g[n]=1;
	for(i=n-1;i>=1;i--){
		g[i]=1;
		for(j=n;j>i;j--)
			if(a[j]<a[i]&&g[j]+1>g[i])
				g[i]=g[j]+1;
	}
	for(i=1;i<n;i++)
		for(j=i+1;j<=n;j++)
			if(f[i]+g[j]>ans)
				ans=f[i]+g[j];
	printf("%d\n",n-ans);
}

int main(){
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%lf",&a[i]);
	process();
	return 0;
}
