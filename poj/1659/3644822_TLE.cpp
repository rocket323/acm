#include <iostream>
using namespace std;

int N, G[11][11], A[11], sum=0;
bool fin;

void init(){
	int i,j,k;
	scanf("%d",&N);
	sum=0;
	fin=false;
	memset(G, 0, sizeof G);
	for(i=1;i<=N;i++){
		scanf("%d",&A[i]);
		sum+=A[i];
	}
}

void out( ){
	int i,j,k;
//	for(i=1;i<=N;i++)
//		for(j=1;j<i;j++)
//			G[i][j]=G[j][i];
	for(i=1;i<=N;i++){
		for(j=1;j<N;j++) cout<<G[i][j]<<' ';
		cout<<G[i][N]<<endl;
	}
}

void dfs(int x, int y){
	int i,j,k;
	if(fin) return;
	if(sum==0){
		fin=true;
		cout<<"YES\n";
		out( );
		return;
	}
	if(y<=N){
		if(A[x]>0&&A[y]>0){
			A[x]--; A[y]--;
			sum-=2; G[x][y]=1; G[y][x]=1;
			dfs(x, y+1);
			if(x<y+1) dfs(x+1, y);
			A[x]++; A[y]++;
			sum+=2; G[x][y]=0; G[y][x]=0;
		}
		dfs(x, y+1);
		if(x<y+1) dfs(x+1, y);
	}
/*	if(x<y-1){
		if(A[x]>0&&A[y]>0){
			A[x]--; A[y]--;
			sum-=2; G[x][y]=1; G[y][x]=1;
			dfs(x+1, y);
			A[x]++; A[y]++;
			sum+=2; G[x][y]=0; G[y][x]=0;
		}
		dfs(x+1, y);
	}*/
}

int main(){
	int i,j,k,T;
//	freopen("1659.in","r",stdin);
	scanf("%d",&T);
	for(i=1;i<=T;i++){
		init();
		dfs(1, 2);
		if(!fin) cout<<"NO\n";
		if(i<T) cout<<endl;
	}
//	while(k=1);
	return 0;
}
