#include <iostream>
#include <cmath>
#define MaxL 10000000
using namespace std;

int N, A[32], arr[32], Min, M[32][32];
bool stop[32], ans[32];

int MinN(int a, int b){
	return(a<b)?a:b;
}

void init(){
	int i,j,k,sum;
	for(i=1;i<=N;i++){
		arr[i]=MaxL;
		scanf("%d",&A[i]);
	}
	for(i=1;i<=31;i++)
		for(j=i;j<=31;j++){
			sum=0;
			for(k=1;k<=N;k++)
				if(i<=A[k]&&A[k]<=j)
					sum++;
			M[i][j]=sum;
		}
	memset(stop, 0, sizeof stop);
	Min=MaxL+1;
}

void dfs(int floor, int Time, int last){
	int Max, i;
	
	for(i=1;i<=N;i++)
		if(A[i]<=last&&arr[i]>Min)
			return;
			
	if(floor==A[N]+1){
		Max=0;
		for(i=1;i<=N;i++)
			if(arr[i]>Max)
				Max=arr[i];
		if(Max<Min){
			Min=Max;
			memcpy(ans, stop, sizeof stop);
		}
		return;
	}
	if(M[last][floor]>0){
		int save[32];
		memcpy(save, arr, sizeof arr);
		for(i=1;i<=N;i++)
			arr[i]=MinN(arr[i], (abs(A[i]-floor)*20)+Time);
		stop[floor]=1;
	
		dfs(floor+1, Time+14, floor);
	
		stop[floor]=0;
		memcpy(arr, save, sizeof save);
	}
	dfs(floor+1, Time+4, last);
}

void out( ){
	int i,j,k=0;
	for(i=1;i<=31;i++)
		if(ans[i]) k++;
	cout<<Min<<endl;
	cout<<k<<' ';
	for(i=1;i<=31;i++)
		if(ans[i]){
			k--;
			if(k) cout<<i<<' ';
			else cout<<i<<endl;
		}
}

int main(){
	int i,j,k;
//	freopen("1771.in","r",stdin);
//	freopen("1771.out","w",stdout);
	scanf("%d",&N);
	while(N!=0){
		init();
		dfs(2, 4, 1);
		out( );
		scanf("%d",&N);
	}
//	while(k=1);
	return 0;
}
