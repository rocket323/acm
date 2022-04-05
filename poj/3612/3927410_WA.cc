#include <iostream>
#define MaxN 100010
using namespace std;

int N, C, A[MaxN], Max, B[MaxN];

void init(){
	int i,j,k;
	scanf("%d%d", &N, &C);
	Max=0;
	for(i=1; i<=N; ++i){
		scanf("%d", &A[i]);
		if(A[i]>Max) Max=A[i];
	}
}

int cntCost(int mid){
	int i,j,k, cost=0;
	for(i=1; i<=N; ++i){
		if(A[i]<mid){
			cost+=(mid-A[i])*(mid-A[i]);
			if(i>1&&A[i-1]>mid)
				cost+=(A[i-1]-mid)*C;
		}
		else cost+=(A[i]-mid)*C;
	}
	return cost;
}

void process(){
	int i,j,k, ans=100000000;
	int rec;
	
	for(i=1; i<=Max; ++i){
		k=cntCost(i);
		if(k<ans){
			ans=k;
		}
	}
	printf("%d\n", ans);
}	

int main(){
	int i,j,k;
//	freopen("3612.in", "r", stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
