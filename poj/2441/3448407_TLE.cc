#include <iostream>
using namespace std;

int num[21],g[21][21],n,m;
int f[1<<21],f1[1<<21];

void init(){
	int i,j,k,t;
	scanf("%d%d",&n,&m);
	memset(num,0,sizeof num);
	for(i=1;i<=n;i++){
		scanf("%d",&t);
		for(j=1;j<=t;j++){
			scanf("%d",&k);
			num[k]++;
			g[k][num[k]]=i;
		}
	}
}

void process(){
	int i,j,k,x,tmp,ans=0;
	int tot=(1<<n)-1;
	memset(f,0,sizeof f);
	memset(f1,0,sizeof f1);
	f1[0]=1;
	for(i=1;i<=m;i++){
		for(j=0;j<=tot;j++){
			for(k=1;k<=num[i];k++){
				x=g[i][k];
				tmp=1<<(x-1);
				
				if((tmp&j)){
					tmp=tmp^j;
					f[j]+=f1[tmp];
					//cout<<i<<' '<<tmp<<' '<<j<<' '<<f[j]<<endl;
					//if(j==tot) ans+=f[j];
				}
			}
			f[j]+=f1[j];
		}
		memcpy(f1,f,sizeof f);
		memset(f,0,sizeof f);
	}
	printf("%d\n",f1[tot]);
}

int main(){
	int i,j,k;
	//freopen("2441.in","r",stdin);
	//freopen("2441.out","w",stdout);
	init();
	process();
	//while(k=1);
	return 0;
}
