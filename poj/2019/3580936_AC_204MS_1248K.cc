#include <iostream>
using namespace std;

int L[251][251], S[251][251], A[251][251];
int Max[251][251], Min[251][251], N, B, Q;

int MaxN(int a, int b){
	return (a>b)?a:b;
}

int MinN(int a, int b){
	return (a<b)?a:b;
}

void init(){
	int i,j,k,rMax, rMin;
	scanf("%d%d%d",&N,&B,&Q);
	for(i=1;i<=N;i++)
		for(j=1;j<=N;j++)
			scanf("%d",&A[i][j]);
	for(k=1;k<=N;k++)
		for(i=1;i<=N+1-B;i++){
			Max[k][i]=-1; Min[k][i]=10000000;
			for(j=i;j<=i+B-1;j++){
				Min[k][i]=MinN(Min[k][i], A[k][j]);
				Max[k][i]=MaxN(Max[k][i], A[k][j]);
			}
		}
	for(i=1;i<=N+1-B;i++)
		for(j=1;j<=N+1-B;j++){
			rMax=-1; rMin=10000000;
			for(k=i;k<=i+B-1;k++){
				rMax=MaxN(rMax, Max[k][j]);
				rMin=MinN(rMin, Min[k][j]);
			}
			L[i][j]=rMax;
			S[i][j]=rMin;
		}
}

void process(){
	int i,j,k, r,c;
	for(i=1;i<=Q;i++){
		scanf("%d%d",&r,&c);
		printf("%d\n",L[r][c]-S[r][c]);
	}
}

int main(){
	int i,j,k;
//	freopen("2019.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
