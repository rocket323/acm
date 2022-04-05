#include <iostream>
using namespace std;

int T, G[100][100], N, M;

void init(){
	int i,j,k, a, b;
	scanf("%d%d", &N, &M);
	memset(G, 0, sizeof G);
	for(i=1; i<=M; i++){
		scanf("%d%d", &a, &b);
		G[a][b]=1;
	}
}

void process(){
	int i,j,k, l, r, ans=0, mid=N/2;
	for(k=1; k<=N; k++)
		for(i=1; i<=N; i++)
			for(j=1; j<=N; j++)
				if(G[i][k]&&G[k][j])
					G[i][j]=1;
	for(i=1; i<=N; i++){
		l=r=0;
		for(j=1; j<=N; j++)
			if(G[j][i]) l++;
			else if(G[i][j]) r++;
		if(l>mid||r>mid) ans++;
	}
	printf("%d\n", ans);
}

int main(){
	int i,j,k,T;
//	freopen("1975.in","r",stdin);
	scanf("%d", &T);
	for(i=1; i<=T; i++){
		init();
		process();
	}
//	while(k=1);
	return 0;
}
