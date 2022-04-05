#include <iostream>
#define Max 100000000
using namespace std;

int n,path,mon;
int g[101][101],num[101]={0},p[101][101],m[101][101];
bool vis[101]={0};

void swap(int k, int i, int j){
	int tmp;
	tmp=g[k][i]; g[k][i]=g[k][j]; g[k][j]=tmp;
	tmp=p[k][i]; p[k][i]=p[k][j]; p[k][j]=tmp;
	tmp=m[k][i]; m[k][i]=m[k][j]; m[k][j]=tmp;
}

void init(){
	int i,j,k,a,b,l,r,t;
	scanf("%d%d%d",&mon,&n,&r);
	for(i=1;i<=r;i++){
		scanf("%d%d%d%d",&a,&b,&l,&t);
		num[a]++;
		g[a][num[a]]=b;
		p[a][num[a]]=l;
		m[a][num[a]]=t;
	}
	for(k=1;k<=n;k++)
		for(i=1;i<num[k];i++)
			for(j=i+1;j<=num[k];j++)
				if(p[k][i]>p[k][j])
					swap(k,i,j);
	vis[1]=1;
	path=Max;
}

void search(int id, int curp, int curm){
	if(curp>path) return;
	if(id==n){
		path=curp;
		return;
	}
	int i,k;
	for(i=1;i<=num[id];i++){
		k=g[id][i];
		if(!vis[k])
			if(curm+m[id][i]<=mon){
				vis[k]=1;
				search(k, curp+p[id][i], curm+m[id][i]);
				vis[k]=0;
			}
	}
}			

int main(){
	//freopen("1724.in","r",stdin);
	init();
	search(1,0,0);
	if(path<Max) printf("%d\n",path);
	else printf("-1\n");
//	int k ; while(k=1);
	return 0;
}
