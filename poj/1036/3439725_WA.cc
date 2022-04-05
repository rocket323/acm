#include <iostream>
using namespace std;

int n,m,T,t[101],p[101],s[101];
bool can[101];
int f[101];

void init(){
	int i,j,k;
	cin>>n>>m>>T;
	for(i=1;i<=n;i++) cin>>t[i];
	for(i=1;i<=n;i++) cin>>p[i];
	for(i=1;i<=n;i++) cin>>s[i];
}

void process(){
	int i,j,k,tmp,ans=0;
	for(i=1;i<n;i++)
		for(j=i+1;j<=n;j++)
			if(t[i]>t[j]){
				tmp=t[i]; t[i]=t[j]; t[j]=tmp;
				tmp=p[i]; p[i]=p[j]; p[j]=tmp;
				tmp=s[i]; s[i]=s[j]; s[j]=tmp;
			}
	s[0]=0; t[0]=0; 
	memset(f,0,sizeof f);
	memset(can,0,sizeof can);
	can[0]=true;
	for(i=1;i<=n;i++){
		for(j=0;j<i;j++)
			if(abs(s[i]-s[j])<=(t[i]-t[j])&&can[j]){
				can[i]=true;
				if(f[i]<f[j]+p[i])
					f[i]=f[j]+p[i];
			}
		if(ans<f[i])
			ans=f[i];
	}
	printf("%d\n",ans);
}

int main(){
	int i,j,k;
	cin>>k;
	for(i=1;i<=k;i++){
		init();
		process();
	}
	return 0;
}
