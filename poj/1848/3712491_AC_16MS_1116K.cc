#include <iostream>
#define MaxL 10000000
using namespace std;

int N, M, G[101][101], nex[101];
int f[101][4], p[101], sz[101];

void init(){
	int i,j,k, a ,b;
	cin>>N;
	memset(nex, 0, sizeof nex);
	for(i=1;i<N;i++){
		cin>>a>>b;
		nex[a]++;
		G[a][nex[a]]=b;
		nex[b]++;
		G[b][nex[b]]=a;
	}
}

void dfs(int now){
	int i,k;
	for(i=1;i<=nex[now];i++){
		k=G[now][i];
		if(p[now]!=k){
			p[k]=now;
			sz[now]++;
			dfs(k);
		}
	}
}

int Min(int a, int b){
	return (a<b)?a:b;
}

int dp(int now, int type){
	
	if(f[now][type]!=-1) return f[now][type];
	
	if(sz[now]==0){
		if(type==1) return 0;
		else return MaxL;
	}
	int i,j,k, ans=MaxL, sum=0, tmp=MaxL;
	if(type==0){
		for(i=1;i<=nex[now];i++){
			k=G[now][i];
			if(p[now]==k) continue;
			sum+=Min(dp(k,2), dp(k,3));
			if(-Min(dp(k,2), dp(k,3))+Min(dp(k,0),dp(k,1))<tmp)
				tmp=-Min(dp(k,2), dp(k,3))+Min(dp(k,0),dp(k,1));
		}
		ans=sum+tmp;
	}
	else if(type==1){
		ans=0;
		for(i=1;i<=nex[now];i++){
			k=G[now][i];
			if(p[now]==k) continue;
			ans+=Min(dp(k,2), dp(k,3));
		}
	}
	else if(type==2){
		for(i=1;i<=nex[now];i++){
			k=G[now][i];
			if(p[now]==k) continue;
			sum+=Min(dp(k,2), dp(k,3));
			if(sz[k]==0) continue;
			if(-Min(dp(k,2), dp(k,3))+dp(k,0)+1<tmp)
				tmp=-Min(dp(k,2), dp(k,3))+dp(k,0)+1;
		}
		ans=sum+tmp;
	}
	else if(type==3){
		if(sz[now]<2) return MaxL;
		for(i=1;i<=nex[now];i++){
			k=G[now][i];
			if(p[now]==k) continue;
			sum+=Min(dp(k,2), dp(k,3));
		}
		int a, b, p1, p2;
		for(i=1;i<=nex[now];i++){
			if(p[now]==G[now][i]) continue;
			a=G[now][i];
			for(j=1;j<=nex[now];j++){
				if(p[now]==G[now][j]) continue;
				b=G[now][j];
				if(i!=j){
					p1=Min(dp(a,0), dp(a,1)); p2=Min(dp(b,0), dp(b,1));
					if(sum-Min(dp(a,2), dp(a,3))-Min(dp(b,2), dp(b,3))+p1+p2+1<ans)
						ans=sum-Min(dp(a,2), dp(a,3))-Min(dp(b,2), dp(b,3))+p1+p2+1;
				}
			}
		}
	}
	f[now][type]=ans;
	return ans;
}		

void process(){
	int k;
	memset(p, -1, sizeof p);
	memset(sz, 0, sizeof sz);
	dfs(1);
	memset(f, -1, sizeof f);
	k=Min(dp(1, 2), dp(1, 3));
	if(k>=MaxL) cout<<-1<<endl;
	else cout<<k<<endl;
}	

int main(){
	int i,j,k;
//	freopen("1848.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
