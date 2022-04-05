#include <iostream>
#define MaxL 100000000
using namespace std;

int S, T, L, M, N;
int G[300][300], f[300], f1[300], AR[300];

int getID(int a){
	for(int i=1; i<=N; i++)
		if(AR[i]==a) return i;
	N++;
	AR[N]=a;
	return N;
}

void init(){
	int i,j,k, w, a, b;
	scanf("%d%d%d%d", &L, &M, &S, &T);
	
	for(i=0; i<300; i++)
		for(j=0; j<300; j++)
			G[i][j]=MaxL;
	
	N=0;
	for(i=1; i<=T; ++i){
		scanf("%d%d%d", &w, &a, &b);
		a=getID(a);
		b=getID(b);
		G[a][b]=G[b][a]=w;
	}
}

int Min(int a, int b){
	return (a<b)?a:b;
}


void process(){
	int i,j,k, ans=MaxL;
	for(i=0; i<300; i++) f[i]=f1[i]=MaxL;
	f[getID(S)]=f1[getID(S)]=0;
	

	for(k=1; k<=L; k++){
		for(i=1; i<=N; i++){
			f[i]=MaxL;
			for(j=1; j<=N; j++)
				f[i]=Min(f[i], f1[j]+G[i][j]);
		}
		for(i=1; i<=N; i++)
			f1[i]=f[i];
			
	}
	printf("%d\n", f[getID(T)]);
}

int main(){
	int i,j,k;
//	freopen("3613.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
