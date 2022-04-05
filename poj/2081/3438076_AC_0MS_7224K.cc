#include <iostream>
using namespace std;

int f[500001],m;
bool vis[5000001];

int main(){
	int i,j,k,n;
	memset(vis,0,sizeof vis);
	m=0; f[0]=0; vis[0]=true;
	scanf("%d",&n);
	while(n!=-1){
		if(n<=m) printf("%d\n",f[n]);
		else{
			for(i=m+1;i<=n;i++){
				k=f[i-1]-i;
				if(k>0&&!vis[k])
					f[i]=k;
				else f[i]=f[i-1]+i;
				vis[f[i]]=true;
			}
			m=n;
			printf("%d\n",f[n]);
		}
		scanf("%d",&n);
	}
	return 0;
}
