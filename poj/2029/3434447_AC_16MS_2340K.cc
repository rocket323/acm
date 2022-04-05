#include <iostream>
using namespace std;

int n,g[501][501],sum[501][501],w,h,s,t;

void init(){
	int i,j,k,x,y;
	scanf("%d%d",&w,&h);
	memset(g,0,sizeof g);
	for(i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		g[x][y]=1;
	}
	scanf("%d%d",&s,&t);
	memset(sum,0,sizeof sum);
	sum[0][1]=0;
	for(i=1;i<=w;i++) sum[i][1]=sum[i-1][1]+g[i][1];
	sum[1][0]=0;
	for(i=1;i<=h;i++) sum[1][i]=sum[1][i-1]+g[1][i];
	for(i=2;i<=w;i++)
		for(j=2;j<=h;j++)
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+g[i][j];
}

void process(){
	int i,j,k,ans=0,ti,tj;
	for(i=s;i<=w;i++)
		for(j=t;j<=h;j++){
			ti=i-s; tj=j-t;
			k=sum[i][j]-sum[i][tj]-sum[ti][j]+sum[ti][tj];
			if(k>ans) ans=k;
		}
	printf("%d\n",ans);
}

int main(){
	int i,j,k;
	scanf("%d",&n);
	while(n!=0){
		init();
		process();
		scanf("%d",&n);
	}
	return 0;
}
