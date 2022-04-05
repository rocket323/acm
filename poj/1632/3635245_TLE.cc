#include <iostream>
#define ADD 37
using namespace std;

int G[77][77], N, M, nex[77];
int A[77], Max;
bool vis[77], in[77];
int cnt[77];

void init(){
	int i,j,k, a, b;
	memset(G,0,sizeof G);
	memset(nex, 0, sizeof nex);
	scanf("%d",&M);
	for(i=1;i<=M;i++){
		scanf("%d%d",&a, &b);
		nex[a]++; G[a][nex[a]]=b+ADD;
		nex[b+ADD]++; G[b+ADD][nex[b+ADD]]=a;
		vis[a]=1;
	}
	N=0;
	for(i=1;i<=36;i++)
		if(vis[i]){
			N++;
			A[N]=i;
		}
}

bool check(int x){
	int i,j,k;
	memset(cnt, 0, sizeof cnt);
	for(i=1;i<=N;i++)
		if(in[i]){
			k=A[i];
			for(j=1;j<=nex[k];j++)
				cnt[G[k][j]]++;
		}
	k=0;
	for(i=37;i<=72;i++)
		if(cnt[i]==x)
			k++;
	if(k==x) return true;
	else return false;
}

void dfs(int dep, int sum ){
	int i,j,k;
	if(sum+N-dep+1<=Max) return;
	if(dep==N+1){
		if(check(sum))
			Max=sum;
		return;
	}
	
	in[dep]=1;
	dfs(dep+1, sum+1);
	in[dep]=0;
	
	dfs(dep+1, sum);
	
}

int main(){
	int i,j,k,T;
//	freopen("1632.in","r",stdin);
	scanf("%d",&T);
	for(i=1;i<=T;i++){
		init();
		Max=0;
		memset(in, 0, sizeof in);
		dfs(1, 0);
		printf("%d\n", Max);
	}
//	while(k=1);
	return 0;
}
