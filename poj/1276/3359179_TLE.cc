#include <iostream>
using namespace std;

bool can[11][200000]={0};
long n,nk[11],w[11],cash;

long process(){
	long i,j,k,t;
	memset(can,0,sizeof can);
	can[0][0]=1;
	for(i=1;i<=n;i++)
		for(j=0;j<=100000;j++)
			if(can[i-1][j])
				for(k=0;k<=nk[i];k++){
					t=j+k*w[i];
					if(t<=100000)
						can[i][t]=1;
				}
	for(i=cash;i>=0;i--)
		if(can[n][i])
			break;
	return i;
}
	
int main(){
	long i,j,k,ans;
	while(cin>>cash){
		cin>>n;
		for(i=1;i<=n;i++) cin>>nk[i]>>w[i];
		ans=process();
		cout<<ans<<endl;
	}
	return 0;
}
