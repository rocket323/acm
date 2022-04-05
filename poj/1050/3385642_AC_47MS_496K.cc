#include <iostream>
using namespace std;

int n,a[101][101],s[101][101]={0},maxn=0;

void process(int x, int y){
	int i,j,k,ans=0;
	k=0;
	for(i=1;i<=n;i++){
		k+=s[i][y]-s[i][x-1];
		if(k<0) k=0;
		if(k>ans) ans=k;
	}
	if(ans>maxn) maxn=ans;
}

int main(){
	int i,j,k;
	cin>>n;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			cin>>a[i][j];
	for(i=1;i<=n;i++){
		s[i][0]=0;
		for(j=1;j<=n;j++)
			s[i][j]=s[i][j-1]+a[j][i];
	}
	for(i=1;i<=n;i++)
		for(j=i;j<=n;j++)
			process(i,j);
	cout<<maxn<<endl;
	return 0;
}
