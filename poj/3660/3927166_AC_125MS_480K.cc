#include <iostream>
using namespace std;

int N, M, G[101][101];

void init(){
	int i,j,k,a, b;
	memset(G, 0, sizeof G);
	cin>>N>>M;
	for(i=1;i<=M;i++){
		cin>>a>>b;
		G[a][b]=1;
	}
}

void process(){
	int i,j,k, ans=0;
	for(k=1;k<=N;k++)
		for(i=1;i<=N;i++)
			for(j=1;j<=N;j++)
				if(G[i][k]&&G[k][j])
					G[i][j]=1;
	for(i=1;i<=N;i++){
		ans++;
		for(j=1;j<=N;j++)
			if(i!=j&&G[i][j]==0&&G[j][i]==0){
				ans--;
				break;
			}
	}
	cout<<ans<<endl;
}

int main(){
	int i,j,k;
//	freopen("1037.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}