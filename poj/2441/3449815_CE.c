#include <stdio.h>


int num[21],g[21][21],n,m,yu[21];
int f[1<<20];
int pow[21];

void init(){
	int i,j,k,t;
	scanf("%d%d",&n,&m);
	memset(num,0,sizeof num);
	memset(yu,0,sizeof yu);
	for(i=1;i<=n;i++){
		scanf("%d",&t);
		for(j=1;j<=t;j++){
			scanf("%d",&k);
			num[k]++;
			g[k][num[k]]=i;
		}
	}
	pow[0]=1;
	for(i=1;i<=n;i++) pow[i]=pow[i-1]*2;
	for(i=1;i<=m;i++)
		for(j=1;j<=num[i];j++){
			k=pow[g[i][j]-1];
			yu[i]=yu[i]|k;
		}
}

void process(){
	int i,j,k,x,tmp,ans=0;
	int tot=(1<<n)-1;
	memset(f,0,sizeof f);
	f[0]=1;
	for(i=1;i<=m;i++){
		for(j=tot;j>0;j--){
			if((j&yu[i])!=0){
				for(k=1;k<=num[i];k++){
					x=g[i][k];
					tmp=pow[x-1];
					if((tmp&j)){
						tmp=tmp^j;
						f[j]+=f[tmp];
					}
				}
			}
		}
	}
	printf("%d\n",f[tot]);
}

void main(){
	int i,j,k;
//	freopen("2441.in","r",stdin);
	init();
	process();
//	while(k=1);
	//return 0;
}
