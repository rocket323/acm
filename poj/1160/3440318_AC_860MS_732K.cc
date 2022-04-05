#include <iostream>
#define MaxL 100000000
using namespace std;

int n,p,a[301],f[301][301];

int cntLen(int s, int t){
	int i,j,sum=0;
	for(i=s+1;i<t;i++)
		if(a[i]-a[s]<a[t]-a[i])
			sum+=a[i]-a[s];
		else
			sum+=a[t]-a[i];
	return sum;
}

int cnt(int x){
	int i,sum=0;
	for(i=x+1;i<=n;i++)
		sum+=a[i]-a[x];
	return sum;
}

int main(){
	int i,j,k,t,x,ans=MaxL;
	scanf("%d%d",&n,&p);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	memset(f,0,sizeof f);
	for(i=1;i<=n;i++){
		f[i][1]=0;
		for(j=1;j<i;j++)
			f[i][1]+=a[i]-a[j];
	}
	for(i=2;i<=n;i++){
		t=i; if(t>p) t=p;
		for(j=2;j<=t;j++){
			f[i][j]=MaxL;
			for(k=1;k<i;k++){
				x=cntLen(k,i);
				if(f[k][j-1]+x<f[i][j])
					f[i][j]=f[k][j-1]+x;
			}
		}
	}
	for(i=p;i<=n;i++){
		x=f[i][p]+cnt(i);
		if(x<ans)
			ans=x;
	}
	printf("%d\n",ans);
	return 0;
}
	
