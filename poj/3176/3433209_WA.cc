#include <iostream>
using namespace std;

int a[360][360],f[360][360],n;

int main(){
	int i,j,k,ans=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		for(j=1;j<=i;j++)
			scanf("%d",&a[i][j]);
	memset(f,0,sizeof f);
	f[1][1]=a[1][1];
	for(i=2;i<=n;i++){
		for(j=1;j<i;j++){
			if(f[i-1][j-1]+a[i][j]>f[i][j]&&j-1>0)
				f[i][j]=f[i-1][j-1]+a[i][j];
			if(f[i-1][j]+a[i][j]>f[i][j])
				f[i][j]=f[i-1][j]+a[i][j];
			if(i==n&&f[i][j]>ans) ans=f[i][j];
		}
	}
	printf("%d\n",ans);
	return 0;
}
