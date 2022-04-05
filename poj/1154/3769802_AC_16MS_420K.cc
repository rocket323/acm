#include <iostream>
using namespace std;

int N, M, ans;
char g[21][21];
bool vis[1000];
int dr[4]={0, -1, 0, 1}, dc[4]={1, 0, -1,0};

void init(){
	int i,j,k;
	cin>>N>>M;
	for(i=1;i<=N;i++)
		for(j=1;j<=M;j++)
			cin>>g[i][j];
	memset(vis, 0, sizeof vis);
}

void dfs(int r, int c, int dep){
	if(dep>ans) ans=dep;
	int k, ii, jj;
	vis[g[r][c]]=1;
	for(k=0;k<4;k++){
		ii=r+dr[k]; jj=c+dc[k];
		if(ii>=1&&ii<=N&&jj>=1&&jj<=M&&!vis[g[ii][jj]])
			dfs(ii, jj, dep+1);
	}
	vis[g[r][c]]=0;
}

int main(){
	int i,j,k;
//	freopen("1154.in","r",stdin);
	init();
	ans=0;
	dfs(1, 1, 1);
	cout<<ans<<endl;
//	while(k=1);
	return 0;
}
