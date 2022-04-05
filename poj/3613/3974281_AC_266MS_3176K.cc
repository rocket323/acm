#include <iostream>
#define MaxL 1000000000
#define MaxN 300
using namespace std;

int S, T, L, M, N;
int G[MaxN][MaxN], f[MaxN], f1[MaxN], AR[MaxN];
int dist[21][MaxN][MaxN];

int getID(int a){
	for(int i=1; i<=N; ++i)
		if(AR[i]==a) return i;
	N++;
	AR[N]=a;
	return N;
}

void init(){
	int i,j,k, w, a, b;
	scanf("%d%d%d%d", &L, &M, &S, &T);
	for(i=0; i<MaxN; ++i)
		for(j=0; j<MaxN; ++j)
			G[i][j]=MaxL;
	N=0;
	for(i=1; i<=M; ++i){
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
	int i,j,k, ans=MaxL, p;
	
	for(i=1; i<=N; ++i)
		for(j=1; j<=N; ++j)
			dist[0][i][j]=G[i][j];
	for(p=1; (1<<p)<=L; ++p)
		for(i=1; i<=N; ++i)
			for(j=1; j<=N; ++j){
				dist[p][i][j]=MaxL;
				for(k=1; k<=N; ++k)
					dist[p][i][j]=Min(dist[p][i][j], dist[p-1][i][k]+dist[p-1][k][j]);
			//	cout<<p<<' '<<i<<' '<<j<<" : "<<dist[p][i][j]<<endl;
			}
	
	
	
	for(i=0; i<=N; ++i) f[i]=f1[i]=MaxL;
	f[getID(S)]=f1[getID(S)]=0;
	
	for(p=0; (1<<p)<=L; ++p){
		if(!(L&(1<<p))) continue;
		for(i=1; i<=N; ++i){
			f[i]=MaxL;
			for(j=1; j<=N; ++j)
				f[i]=Min(f[i], f1[j]+dist[p][i][j]);
		}
		for(i=1; i<=N; ++i) f1[i]=f[i];
	}


	printf("%d\n", f[getID(T)]);
}

int main(){
	int i,j,k;
//	freopen("relays.9.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
