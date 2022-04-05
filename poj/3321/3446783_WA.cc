#include <iostream>
#include <string>
#define MaxL 100010
using namespace std;

int sum[MaxL]={0},pre[MaxL]={0},n,son[MaxL][50]={0},tp[MaxL]={0};
int a[MaxL]={0}, ord[MaxL]={0}; 
int kk[MaxL]={0},tag[MaxL]={0};
int tot=0;

void label(int now){
	int i,j,k;
	for(i=1;i<=tp[now];i++){
		k=son[now][i];
		label(k);
	}
	tot++;
	ord[now]=tot;
}

void init(){
	int i,j,k,u,v;
	scanf("%d",&n);
	for(i=1;i<=n;i++) { tag[i]=1;}
	memset(a,0,sizeof a);
	for(i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		tp[u]++;
		if(tp[u]>1) pre[v]=son[u][tp[u]-1];
		son[u][tp[u]]=v;
	}
	label(1);
}

int lowbit(int x){
	return x&(-x);
}

void add(int x, int num){
	while(x<=n){
		a[x]+=num;
		x+=lowbit(x);
	}
}

int getsum(int x){
	int ans=0;
	while(x>0){
		ans+=a[x];
		x-=lowbit(x);
	}
	return ans;
}

int main(){
	int i,j,k,q;
	char s[5];
	init();
	for(i=1;i<=n;i++){add(i,1);}
	scanf("%d",&q);
	for(i=1;i<=q;i++){
		scanf("%s%d",s,&k);
		if(s[0]=='C'){
			if(tag[ord[k]]==0){
				tag[ord[k]]=1;
				add(ord[k],1);
			}
			else{
				tag[ord[k]]=0;
				add(ord[k],-1);
			}
		}
		else printf("%d\n",getsum(ord[k])-getsum(ord[pre[k]]));
	}
	return 0;
}
