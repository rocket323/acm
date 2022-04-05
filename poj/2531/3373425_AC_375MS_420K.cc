#include <iostream>
using namespace std;

int n,g[30][30],ans=0;
bool label[30];

void search(int x,int sum){
	int i,j,tmp=sum;
	if(x==n+1){
		if(sum>ans)
			ans=sum;
		return;
	}
	label[x]=0;
	for(i=1;i<x;i++)
		if(label[i])
			tmp+=g[x][i];
	search(x+1,tmp);
	label[x]=1; tmp=sum;
	for(i=1;i<x;i++)
		if(!label[i])
			tmp+=g[x][i];
	search(x+1,tmp);
}

int main(){
	int i,j,k;
	cin>>n;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			cin>>g[i][j];
	memset(label,0,sizeof label);
	search(1,0);
	cout<<ans<<endl;
	return 0;
}

