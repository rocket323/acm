#include <iostream>
using namespace std;

int col[101][101],N,M;
char G[101][101];
int dn[8]={0,-1,-1,-1,0,1,1,1},
	dm[8]={1,1,0,-1,-1,-1,0,1};

void init(){
	int i,j,k;
	scanf("%d%d",&N,&M);
	for(i=1;i<=N;i++)
		for(j=1;j<=M;j++)
			cin>>G[i][j];
}

void dfs(int x, int y, int co){
	col[x][y]=co;
	int i, ii, jj;
	for(i=0;i<8;i++){
		ii=x+dn[i]; jj=y+dm[i];
		if(ii>=1&&ii<=N&&jj>=1&&jj<=M&&G[ii][jj]=='W'&&col[ii][jj]==0)
			dfs(ii, jj, co);
	}
}

void process(){
	int i,j,k,ans=0;
	memset(col, 0, sizeof col);
	for(i=1;i<=N;i++)
		for(j=1;j<=M;j++)
			if(G[i][j]=='W'&&col[i][j]==0){
				ans++;
				dfs(i,j,ans);
			}
	printf("%d\n",ans);
}

int main(){
	int i,j,k;
//	freopen("2386.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
