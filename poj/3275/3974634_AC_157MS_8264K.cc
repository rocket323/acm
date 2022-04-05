#include <iostream>
#define MaxN 1001
using namespace std;

int N, M, nex[MaxN], G[MaxN][MaxN], can[MaxN][MaxN];
bool vis[MaxN];

void dfs(int k, int now){
	can[k][now]=1;
	for(int i=1; i<=nex[now]; ++i){
		int p=G[now][i];
		if(!vis[p]){
			vis[p]=1;
			dfs(k, p);
		}
	}
}	

void process(){
	int i,j,k, ans=0;
	memset(can, 0, sizeof can);
	memset(vis, 0, sizeof vis);
	for(i=1; i<=N; i++){
		memset(vis, 0, sizeof vis);
		vis[i]=1;
		dfs(i, i);
	}

		
	for(i=1; i<=N; i++)
		for(j=i+1; j<=N; ++j)
			if(can[i][j]==0&&can[j][i]==0) ans++;
	
	printf("%d\n", ans);
}

int main(){
	int i,j,k, a, b;
//	freopen("3275.in", "r", stdin);
	scanf("%d%d", &N, &M);
	memset(nex, 0, sizeof nex);
	for(i=1; i<=M; i++){
		scanf("%d%d", &a, &b);
		nex[a]++;
		G[a][nex[a]]=b;
	}
	process();
//	while(1);
	return 0;
}
