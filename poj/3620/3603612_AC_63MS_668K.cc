#include <iostream>
using namespace std;

int col[101][101], cnt[10001],N,M, G[101][101];
int di[4]={0,-1,0,1}, dj[4]={1,0,-1,0};

void init(){
	int i,j,k,r,c;
	scanf("%d%d%d",&N,&M,&k);
	memset(G,0,sizeof G);
	for(i=1;i<=k;i++){
		scanf("%d%d",&r,&c);
		G[r][c]=1;
	}
	memset(col,0,sizeof col);
	memset(cnt,0,sizeof cnt);
}

void dfs(int i, int j, int color){
	col[i][j]=color;
	cnt[color]++;
	int ti, tj,k;
	for(k=0;k<4;k++){
		ti=i+di[k]; tj=j+dj[k];
		if(ti>=1&&ti<=N&&tj>=1&&tj<=M&&G[ti][tj]==1&&col[ti][tj]==0){
			dfs(ti, tj, color);
		}
	}
}

void process(){
	int i,j,k,ans=0, color=0;
	for(i=1;i<=N;i++)
		for(j=1;j<=M;j++)
			if(col[i][j]==0&&G[i][j]){
				color++;
				dfs(i,j,color);
			}
	for(i=1;i<=color;i++)
		if(ans<cnt[i])
			ans=cnt[i];
	printf("%d\n",ans);
}

int main(){
	int i,j,k;
//	freopen("3620.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
