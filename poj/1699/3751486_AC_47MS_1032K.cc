#include <iostream>
using namespace std;

char S[11][21];
int N, d[21][21], ans;
bool vis[21];

void make(int a, int b){
	int i,j,k, l1, l2, s1, s2;
	l1=strlen(S[a]); l2=strlen(S[b]);
	for(i=0;i<l1;i++){
		if(l1-i>l2) continue;
		s1=i; s2=0;
		while(s1<l1){
			if(S[a][s1]!=S[b][s2]) break;
			s1++; s2++;
		}
		if(s1==l1){
			d[a][b]=l2-l1+i;
			return;
		}
	}
	d[a][b]=l2;
}

void init(){
	int i,j,k;
	scanf("%d",&N);
	for(i=1;i<=N;i++)
		scanf("%s",S[i]);
	for(i=1;i<=N;i++)
		for(j=1;j<=N;j++)
			if(i==j) d[i][j]=0;
			else make(i, j);
}

void dfs(int lab, int len, int depth){
	if(len>=ans) return;
	if(depth==N){
		ans=len;
		return;
	}
	int i;
	for(i=1;i<=N;i++){
		if(vis[i]) continue;
		vis[i]=1;
		dfs(i, len+d[lab][i], depth+1);
		vis[i]=0;
	}
}

void process(){
	int i,j,k;
	ans=10000000;
	for(i=1;i<=N;i++){
		memset(vis, 0, sizeof vis);
		vis[i]=1;
		dfs(i, strlen(S[i]), 1);
	}
	printf("%d\n",ans);
}

int main(){
	int i,j,k,T;
//	freopen("1699.in","r",stdin);
	scanf("%d",&T);
	for(i=1;i<=T;i++){
		init();
		process();
	}
//	while(k=1);
	return 0;
}
