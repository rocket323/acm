#include <iostream>
using namespace std;

int n,g[6001][100],a[6001],f[6001][2];
int num[6001],pre[6001];
bool cnt[6001][2];

int Max(int u, int v){
	return (u>v)?u:v;
}

void init(){
	int i,j,k,u,v;
	memset(num,0,sizeof num);
	memset(pre,0,sizeof pre);
	memset(cnt,0,sizeof cnt);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	for(i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		num[v]++;
		pre[u]=v;
		g[v][num[v]]=u;
	}
}

int dp(int now, int join){
	int i,j,k;
	if(cnt[now][join]) return f[now][join];
	if(join==0){
		int sum=0;
		for(i=1;i<=num[now];i++){
			k=g[now][i];
			sum+=Max(dp(k,1), dp(k,0));
		}
		cnt[now][join]=1;
		f[now][join]=sum;
		return sum;
	}
	else{
		int sum=a[now];
		for(i=1;i<=num[now];i++){
			k=g[now][i];
			sum+=dp(k,0);
		}
		cnt[now][join]=1;
		f[now][join]=sum;
		return sum;
	}
}

void process(){
	int i,j,k;
	for(i=1;i<=n;i++)
		if(pre[i]==0){
			k=i;
			break;
		}
	printf("%d\n",Max(dp(k,0), dp(k,1)));
}

int main(){
	int i,j,k;
	scanf("%d",&n);
	while(n!=0){
		init();
		process();
		scanf("%d",&n);
	}
	return 0;
}
