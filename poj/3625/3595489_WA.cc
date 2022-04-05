#include <iostream>
#define MaxL 10000000
#include <cmath>
using namespace std;

int N,M, x[1001], y[1001], closet[1001];
double d[1001][1001], lowcost[1001];
bool S[1001];

void calLen(){
	int i,j,k;
	memset(d,0,sizeof d);
	for(i=1;i<=N;i++)
		for(j=1;j<=N;j++)
			if(i!=j)
				d[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}

void buildLink(){
	int i,j,k,rec;
	double Min;
	for(i=1;i<=N;i++)
		if(!S[i]){
			Min=MaxL;
			for(j=1;j<=N;j++)
				if(S[j]&&d[i][j]<Min){
					Min=d[i][j];
					rec=j;
				}
			lowcost[i]=Min;
			closet[i]=rec;
		}
}

void init(){
	int i,j,k,t,rec;
	double Min,ans=0;
	scanf("%d%d",&N,&M);
	for(i=1;i<=N;i++)
		scanf("%d%d",&x[i], &y[i]);
	calLen();
	memset(S,0,sizeof S);
	for(k=1;k<=M;k++){
		scanf("%d%d",&i,&j);
		S[i]=1; S[j]=1;
	}
	buildLink();
	for(t=1;t<=N-1-M;t++){
		Min=MaxL;
		for(i=1;i<=N;i++)
			if(!S[i]&&lowcost[i]<Min){
				rec=i;
				Min=lowcost[i];
			}
		S[rec]=true;
		ans+=Min;
		for(i=1;i<=N;i++){
			if(!S[i]&&lowcost[i]>d[i][rec]){
				lowcost[i]=d[i][rec];
				closet[i]=rec;
			}
		}
	}
	printf("%.2f\n",ans);
}

int main(){
	int i,j,k;
//	freopen("3625.in","r",stdin);
	init();
//	while(k=1);
	return 0;
}
