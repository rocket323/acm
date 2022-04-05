#include <iostream>
#define MaxL 10000000
using namespace std;

int A[8][8],n,s[8],Min,C[8];

void init(){
	int i,j,k;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&A[i][j]);
}

void cnt(){
	int i,j,k, Max=-MaxL;
	for(i=0;i<n;i++)
		if(C[i]>Max) Max=C[i];
	if(Max<Min) Min=Max;
}

void search(int nd){
	int i,j,k;
	for(i=0;i<n;i++){
		s[nd]=i;
		for(j=0;j<n;j++){
			k=(j+i)%n;
			C[k]+=A[nd][j];
		}
		if(nd<n-1) search(nd+1);
		else
			cnt();
		for(j=0;j<n;j++){
			k=(j+i)%n;
			C[k]-=A[nd][j];
		}
	}
}

void process(){
	int i,j,k;
	Min=MaxL;
	memset(C,0,sizeof C);
	search(0);
	printf("%d\n",Min);
}

int main(){
	int i,j,k;
//	freopen("2078.in","r",stdin);
	scanf("%d",&n);
	while(n!=-1){
		init();
		process();
		scanf("%d",&n);
	}
//	while(k=1);
	return 0;
}
