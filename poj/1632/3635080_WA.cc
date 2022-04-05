#include <iostream>
#define ADD 37
using namespace std;

int G[77][77], N, M, nex[77];
bool vis[77];
int cnt[77];

void init(){
	int i,j,k, a, b;
	memset(G,0,sizeof G);
	memset(nex, 0, sizeof nex);
	scanf("%d",&M);
	for(i=1;i<=M;i++){
		scanf("%d%d",&a, &b);
		nex[a]++; G[a][nex[a]]=b+ADD;
		nex[b+ADD]++; G[b+ADD][nex[b+ADD]]=a;
		vis[a]=1;
	}
	N=0;
	for(i=1;i<=36;i++)
		if(vis[i]) N++;		
}

bool check(int x){
	int i,j,k;
	memset(cnt, 0, sizeof cnt);
	for(i=1;i<=32;i++)
		if(vis[i]){
			for(j=1;j<=nex[i];j++)
				cnt[G[i][j]]++;
		}
	k=0;
	for(i=1;i<=76;i++)
		if(cnt[i]>=x)
			k++;
	if(k>=x) return true;
	else return false;
}

void process(){
	int i,j,k;
	for(i=N;i>=1;i--)
		if(check(i)) break;
	printf("%d\n",i);
}

int main(){
	int i,j,k,T;
//	freopen("1632.in","r",stdin);
	scanf("%d",&T);
	for(i=1;i<=T;i++){
		init();
		process();
	}
//	while(k=1);
	return 0;
}
