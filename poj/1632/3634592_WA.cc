#include <iostream>
#define ADD 37
using namespace std;

int G[76][76], N, nex[76], ans, M[76][76];
bool vis[37], F[77];

void init(){
	int i,j,k, a, b;
	memset(G,0,sizeof G);
	memset(nex, 0, sizeof nex);
	memset(vis, 0, sizeof vis);
	memset(M, 0, sizeof M);
	scanf("%d",&N);
	for(i=1;i<=N;i++){
		scanf("%d%d",&a, &b);
		nex[a]++; G[a][nex[a]]=b+ADD;
		nex[b+ADD]++; G[b+ADD][nex[b+ADD]]=a;
		M[a][b+ADD]=1; M[b+ADD][a]=1;
		vis[a]=1;
	}
	ans=0;
}

int Max(int a, int b){
	return(a>b)?a:b;
}

void dfs(int now){
	int i;
	F[now]=1;
	for(i=1;i<=nex[now];i++)
		if(!F[G[now][i]])
			dfs(G[now][i]);
}

bool check(int x){
	int i,j,k, sum1=0, sum2=0;
	memset(F, 0, sizeof F);
	dfs(x);
	/*if(x==11){
		for(i=1;i<=76;i++)
			if(F[i]) cout<<i<<endl;
		cout<<nex[x]<<endl;
	}*/
	for(i=1;i<=36;i++)
		for(j=37;j<=72;j++){
			
			if(F[i]&&F[j]){
				if(x==11)
				//	cout<<i<<' '<<j<<' '<<G[i][j]<<endl;
				if(!M[i][j]) return false;
			
			}
		}
	for(i=1;i<=36;i++) if(F[i]) sum1++;
	for(i=37;i<=72;i++) if(F[i]) sum2++;
	if(sum1<nex[x]||sum2<nex[x]) return false;
	return true;
}

void process(){
	int i,j,k;
//	for(i=1;i<=76;i++) if(vis[i]) cout<<i<<endl;
	for(i=1;i<=36;i++)
		if(vis[i]&&check(i))
			ans=Max(ans, nex[i]);
	printf("%d\n",ans);
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
