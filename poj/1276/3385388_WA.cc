#include <iostream>
using namespace std;

bool can[100001]={0};
int n,nk[11],w[11],cash;
int b[100001][1]={0};
int process(){
	int i,j,k,t,tmp;
	memset(can,0,sizeof can);
	memset(b,0,sizeof b);
	can[0]=1;
	for(i=1;i<n;i++)
		for(j=i+1;j<=n;j++)
			if(w[i]>w[j]){
				tmp=w[i]; w[i]=w[j]; w[j]=tmp;
				tmp=nk[i]; nk[i]=nk[j]; nk[j]=tmp;
			}
	
	for(i=1;i<=n;i++){
		t=w[i]*nk[i];
		if(t>cash) t=cash;
		for(j=w[i];j<=t;j++){
			if(can[j]) continue;
			tmp=j-w[i];
			if(can[tmp]){
				if(b[tmp][0]==i&&b[tmp][1]<nk[i]){
					b[j][0]=i;
					b[j][1]++;
					can[j]=true;
				}
				else if(b[tmp][0]!=i){
					b[j][0]=i;
					b[j][1]=1;
					can[j]=true;
				}
			}
		}
	}
				
	for(i=cash;i>=0;i--)
		if(can[i])
			break;
	return i;
}

int main(){
	int i,j,k,ans;
	while(cin>>cash){
		cin>>n;
		for(i=1;i<=n;i++) cin>>nk[i]>>w[i];
		ans=process();
		cout<<ans<<endl;
	}
	return 0;
}
