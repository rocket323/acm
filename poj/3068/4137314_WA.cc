#include <iostream>
#include <stdio.h>
#include <string.h>
#define MaxN 65
#define MaxL 10000000
using namespace std;

int buf[MaxN][MaxN];
int N, M, G[MaxN][MaxN], cnt[MaxN], lv[MaxN][MaxN];
int flag, res;
int vis[MaxN], orz[MaxN];

void init(){
	int i,j,k;
	int a, b, c, flag;
	memset(cnt, 0, sizeof cnt);
	memset(orz, 0, sizeof orz);
	memset(lv, 0, sizeof lv);
	for(i=1; i<=M; ++i){
		scanf("%d%d%d", &a, &b, &c);
		flag=0;
		for(j=1; j<=cnt[a]; ++j){
			if(buf[a][j]==b){
				flag=1;
				if(G[a][j]>c){
					G[a][j]=c;
					lv[a][j]=i;
				}
			}
		}
		if(a==0||a==N-1||b==0||b==N-1) flag=0;
		if(!flag){
			++cnt[a]; buf[a][cnt[a]]=b; G[a][cnt[a]]=c;
			lv[a][cnt[a]]=i;
		}
	}
}

void dfs2(int now, int cost){
	if(cost>=res) return;
	if(now==N-1){
		res=cost;
		return;
	}
	int i,j,k;
	for(i=1; i<=cnt[now]; ++i){
		k=buf[now][i];
		if(vis[k]&&k!=N-1) continue;
		if(orz[lv[now][i]]) continue;
		vis[k]=1; orz[lv[now][i]]=1;
		dfs2(k, cost+G[now][i]);
		vis[k]=0; orz[lv[now][i]]=0;
	}
}

void dfs(int now, int cost){
	if(cost>=res) return;
	if(now==N-1){
		dfs2(0, cost);
		return;
	}
	int i, j, k;
	for(i=1; i<=cnt[now]; ++i){
		k=buf[now][i];
		if(vis[k]&&k!=N-1) continue;
		if(orz[lv[now][i]]) continue;
		vis[k]=1; orz[lv[now][i]]=1;
		dfs(k, cost+G[now][i]);
		vis[k]=0; orz[lv[now][i]]=0;
	}
}

void process(int tes){
	int i,j,k;
	res=MaxL;
	printf("Instance #%d: ", tes);
	memset(vis, 0, sizeof vis);
	dfs(0, 0);
	if(res==MaxL) printf("Not possible\n");
	else printf("%d\n", res);
}

int main(){
	int k=0;
//	freopen("2927.in", "r", stdin);
	scanf("%d%d", &N, &M);
	while(N!=0){
		init();
		process(++k);
		scanf("%d%d", &N, &M);
	}
//	while(1);
	return 0;
}
