#include <iostream>
#define MaxL 1000000
using namespace std;

int N, M, D[150], A[150], f[2001][2001];
char S[3000];

void init(){
	int i,j,k, a, b;
	char ch;
	cin>>M>>N;
	cin>>S;
	for(i=1; i<=M; i++){
		cin>>ch>>a>>b;
		A[(int)ch]=a;
		D[(int)ch]=b;
	}
}

int Min(int a, int b){
	return (a<b)?a:b;
}

void process(){
	int i,j,k;
	for(i=0; i<=N; i++)
		for(j=0; j<=N; j++)
			if(j<=i)
				f[i][j]=0;
			else f[i][j]=MaxL;
	for(k=2; k<=N; k++)
		for(i=0; i<=N-k; i++){
			j=i+k-1;
			f[i][j]=MaxL;
			if(S[i]==S[j])f[i][j]=f[i+1][j-1];
			f[i][j]=Min(f[i][j], f[i+1][j]+A[S[i]]);
			f[i][j]=Min(f[i][j], f[i+1][j]+D[S[i]]);
			f[i][j]=Min(f[i][j], f[i][j-1]+A[S[j]]);
			f[i][j]=Min(f[i][j], f[i][j-1]+D[S[j]]);
		}
	cout<<f[0][N-1]<<endl;
	
	
}

int main(){
	int i,j,k;
//	freopen("3280.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
