#include <iostream>
#define MaxL 100000000
using namespace std;

int G[101][101], N, S, T, d[101];
bool vis[101];

void init(){
	int i,j,k,c;
	scanf("%d%d%d",&N,&S,&T);
	for(i=1;i<=N;i++)
		for(j=1;j<=N;j++)
			G[i][j]=MaxL;
	for(i=1;i<=N;i++){
		scanf("%d",&k);
		for(j=1;j<=k;j++){
			scanf("%d",&c);
			if(j==1) G[i][c]=0;
			else G[i][c]=1;
		}
	}
}

void process(){
	int i,j,k, Min;
	for(i=1;i<=N;i++) d[i]=MaxL;
	memset(vis,0,sizeof vis);
	d[S]=0;
	for(j=1;j<=N;j++){
		Min=MaxL;
		for(i=1;i<=N;i++)
			if(d[i]<Min&&!vis[i]){
				k=i;
				Min=d[i];
			}
		vis[k]=true;
		for(i=1;i<=N;i++)
			if(d[k]+G[k][i]<d[i])
				d[i]=d[k]+G[k][i];
	}
	if(d[T]==MaxL) printf("-1\n");
	else printf("%d\n",d[T]);
}

int main(){
	int i,j,k;
//	freopen("1847.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
