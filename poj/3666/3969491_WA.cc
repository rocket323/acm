#include <iostream>
#include <algorithm>
#include <cmath>
#define MaxN 2001
#define MaxL 10000000
using namespace std;

int N, A[MaxN], f[MaxN][MaxN], l[MaxN], h[MaxN], B[MaxN];
int pos[MaxN], rank[MaxN];

int Min(int a, int b){
	return(a<b)?a:b;
}

int process(){
	int i,j,k, ans=MaxL, tmp;
	for(i=0; i<N; i++) f[1][i]=abs(B[i]-A[0]);
	h[N-1]=f[0][N-1];
	for(i=N-2; i>=0; i--) h[i]=Min(h[i+1], f[0][i]);
	l[0]=f[0][0];
	for(i=1; i<N; i++) l[i]=Min(h[i-1], f[0][i]);
	
	for(i=1; i<N; i++){
		for(j=0; j<N; j++){
			f[i][j]=h[j]+abs(B[j]-A[i]);
		}
		h[N-1]=f[i][N-1];
		for(j=N-2; j>=0; j--) h[j]=Min(h[j+1], f[i][j]);
	}
	for(i=0; i<N; i++)
		if(f[N-1][i]<ans)
			ans=f[N-1][i];
	return ans;
}

int process2(){
	int i,j,k, ans=MaxL, tmp;
	for(i=0; i<N; i++) f[1][i]=abs(B[i]-A[0]);
	l[0]=f[0][0];
	for(i=1; i<N; i++) l[i]=Min(h[i-1], f[0][i]);
	
	for(i=1; i<N; i++){
		for(j=0; j<N; j++){
			f[i][j]=l[j]+abs(B[j]-A[i]);
		}
		l[0]=f[i][0];
		for(j=1; j<N; j++) l[j]=Min(l[j-1], f[i][j]);
	}
	for(i=0; i<N; i++)
		if(f[N-1][i]<ans)
			ans=f[N-1][i];
	return ans;
}

int main(){
	int i,j,k;
//	freopen("3666.in", "r", stdin);
	scanf("%d", &N);
	for(i=0; i<N; ++i){
		scanf("%d", &A[i]);
		B[i]=A[i];
	}
	sort(B, B+N);
	cout<<Min(process(), process2())<<endl;
	
//	while(1);
	return 0;
}
	
