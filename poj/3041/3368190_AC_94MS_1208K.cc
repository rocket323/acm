#include <iostream>
using namespace std;

int n,m,ans,g[501][501]={0},link[501]={0};
bool used[501];

void init(){
	int i,j,k,a,b;
	cin>>n>>m;
	for(i=1;i<=m;i++){
		cin>>a>>b;
		g[a][b]=1;
	}
}

bool can(int x){
	int i,j,k;
	for(i=1;i<=n;i++)
		if(!used[i]&&g[x][i]){
			used[i]=true;
			if(link[i]==0||can(link[i])){
				link[i]=x;
				return true;
			}
		}
	return false;
}

int maxMatch(){
	int i,j,k,num;
	num=0;
	memset(link,0,sizeof link);
	for(i=1;i<=n;i++){
		memset(used,0,sizeof used);
		if(can(i)) num++;
	}
	return num;
}

int main(){
	int i,j,k;
	init();
	k=maxMatch();
	cout<<k<<endl;
	return 0;
}
