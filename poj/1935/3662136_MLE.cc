#include <iostream>
using namespace std;

int N,S, G[50001][61], nex[50001];
int L[50001][61];
bool vis[50001], use[50001];

void find( int now ){
	int i,k;
	use[now]=1;
	for(i=1;i<=nex[now];i++){
		k=G[now][i];
		if(!use[k]){
			find(k);
			if(vis[k]) vis[now]=1;
		}
	}
}

void init(){
	int i,j,k,a ,b, c;
	scanf("%d%d",&N, &S);
	memset(nex, 0, sizeof nex);
	for(i=1;i<N;i++){
		scanf("%d%d%d",&a, &b, &c);
		nex[a]++; G[a][nex[a]]=b; L[a][nex[a]]=c;
		nex[b]++; G[b][nex[b]]=a; L[b][nex[b]]=c;
	}
	memset(vis, 0, sizeof vis);
	scanf("%d",&k);
	for(i=1;i<=k;i++){
		scanf("%d",&j);
		vis[j]=1;
	}
	memset(use, 0, sizeof use);
	find(S);
	memset(use, 0, sizeof use);
}

int DP(int now ){
	int i,j,k,ans[61],c, Max=0, sum=0;
	k=0;
	use[now]=1;
	for(i=1;i<=nex[now];i++){
		c=G[now][i];
		if(vis[c]&&!use[c]){
			k++;
			ans[k]=DP(c)+L[now][i];
			sum+=ans[k];
			if(ans[k]>Max) Max=ans[k];
		}
	}
	return 2*sum-Max;
}

void process(){
	int i,j,k;
	printf("%d\n",DP(S));
}

int main(){
	int i,j,k;
//	freopen("1935.in","r",stdin);
//	scanf("%d%d",&N,&S);
//	while(N!=0){
		init();
		process();
//		scanf("%d%d",&N,&S);
//	}
//	while(k=1);
	return 0;
}
