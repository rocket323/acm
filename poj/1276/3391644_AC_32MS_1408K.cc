#include <iostream>
using namespace std;

int cash,n,sum,w[100001],nk[100001],b[100001][2];
bool can[200001];

int dp(){
	int i,j,k,t,tmp;
	memset(can,0,sizeof can);
	memset(b,0,sizeof b);
	can[0]=1; t=0;
	for(i=1;i<=n;i++){
		t+=w[i]*nk[i];
		if(t>cash) t=cash;
		for(j=w[i];j<=t;j++){
			if(can[j]) continue;
			tmp=j-w[i];
			if(can[tmp]){
				if(b[tmp][0]==i&&b[tmp][1]<nk[i]){
					b[j][0]=i;
					can[j]=true;
					b[j][1]=b[tmp][1]+1;
				}
				else if(b[tmp][0]!=i&&nk[i]>0){
					can[j]=true;
					b[j][0]=i;
					b[j][1]=1;
				}
			}
		}
	}
	for(i=cash;i>=0;i--)
		if(can[i]) break;
	return i;
}

int main(){
	int i,j,k;
	while(cin>>cash){
		cin>>n;
		for(i=1;i<=n;i++)
			cin>>nk[i]>>w[i];
		k=dp();
		cout<<k<<endl;
	}
	return 0;
}
