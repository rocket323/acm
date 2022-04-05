#include <iostream>
#define MaxL 100000000
using namespace std;

int n,lowcost[101],closet[101],g[101][101];
bool s[101];

void init(){
	int i,j,k;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&g[i][j]);
}

void process(){
	int i,j,k,tot,min,rec;
	tot=0;
	memset(s,0,sizeof s);
	s[1]=true;
	for(i=2;i<=n;i++){
		closet[i]=1;
		lowcost[i]=g[i][1];
	}
	for(i=1;i<n;i++){
		min=MaxL;
		for(j=2;j<=n;j++)
			if(lowcost[j]<min&&!s[j]){
				rec=j;
				min=lowcost[j];
			}
		s[rec]=true;
		tot+=min;
		for(k=2;k<=n;k++)
			if(lowcost[k]>g[k][rec]&&!s[k]){
				lowcost[k]=g[k][rec];
				closet[k]=rec;
			}
	}
	cout<<tot<<endl;
}
		
int main(){
	int k;
	while(cin>>n){
		init();
		process();
	}
	return 0;
}
