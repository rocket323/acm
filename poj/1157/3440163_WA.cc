#include <iostream>
using namespace std;

int n,v,f[101][101],a[101][101];

int Max(int x, int y){
	return (x>y)? x : y;
}

int main(){
	int i,j,k,ans=0,t;
	//freopen("1157.in","r",stdin);
	while(cin>>n){
	
	scanf("%d",&v);
	for(i=1;i<=n;i++)
		for(j=1;j<=v;j++)
			scanf("%d",&a[i][j]);
	memset(f,0,sizeof f);
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
	}
	//while(k=1); 
	return 0;
}
