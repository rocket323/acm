#include <iostream>
#define MaxL 1000000
#include <cmath>
using namespace std;

int n,m,mt,ht,link[101],mx[101],my[101],hx[101],hy[101];
int labelx[101],labely[101];
int g[101][101],f[101][101];
bool x[101],y[101];

void init(){
	int i,j,k;
	char ch;
	mt=0; ht=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++){
			cin>>ch;
			if(ch=='m'){
				mt++;
				mx[mt]=i; my[mt]=j;
			}
			else if(ch=='H'){
				ht++;
				hx[ht]=i; hy[ht]=j;
			}
		}
	for(i=1;i<=mt;i++)
		for(j=1;j<=ht;j++){
			g[i][j]=abs(mx[i]-hx[j])+abs(my[i]-hy[j]);
			f[i][j]=MaxL-g[i][j];
		}
}

bool find(int v){
	int i,j,k;
	x[v]=true;
	for(i=1;i<=ht;i++)
		if(!y[i]&&labelx[v]+labely[i]==f[v][i]){
			y[i]=true;
			if(link[i]==0||find(link[i])){
				link[i]=v;
				return true;
			}
		}
	return false;
}

void process(){
	int i,j,k,min,ans;
	memset(labelx,0,sizeof labelx);
	memset(labely,0,sizeof labely);
	memset(link,0,sizeof link);
	for(i=1;i<=mt;i++)
		for(j=1;j<=ht;j++)
			if(labelx[i]<f[i][j])
				labelx[i]=f[i][j];
	for(k=1;k<=mt;k++){
		while(true){
			memset(x,0,sizeof x); memset(y,0,sizeof y);
			if(find(k)) break;
			min=MaxL;
			for(i=1;i<=mt;i++)
				if(x[i])
					for(j=1;j<=ht;j++)
						if(!y[j])
							if(labelx[i]+labely[j]-f[i][j]<min)
								min=labelx[i]+labely[j]-f[i][j];
			for(i=1;i<=mt;i++)
				if(x[i]) labelx[i]-=min;
			for(i=1;i<=ht;i++)
				if(y[i]) labely[i]+=min;
		}
	}
	ans=0;
	for(i=1;i<=ht;i++) ans+=g[link[i]][i];
	cout<<ans<<endl;
}

int main(){
	int i,j,k;
	cin>>n>>m;
	while(n!=0){
		init();
		process();
		cin>>n>>m;
	}
	return 0;
}
