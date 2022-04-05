#include <iostream>
#define MaxN 10000000
using namespace std;

int n,v,f[101][101],a[101][101];

int Max(int x, int y){
	return (x>y)? x : y;
}

int main(){
	int i,j,k,ans,t;
	ans=-1*MaxN;
	scanf("%d%d",&n,&v);
	for(i=1;i<=n;i++)
		for(j=1;j<=v;j++)
			scanf("%d",&a[i][j]);
	memset(f,0,sizeof f);
	for(i=0;i<=v;i++)
		for(j=i+1;j<=n;j++)
			f[i][j]=-1*MaxN;
	for(i=1;i<=v;i++){
		t=i;
		if(t>n) t=n;
		for(j=1;j<=t;j++){
			f[i][j]=Max(f[i-1][j], f[i-1][j-1]+a[j][i]);
			if(j==n&&f[i][j]>ans)
				ans=f[i][j];
		}
	}
	printf("%d\n",ans);
	return 0;
}
