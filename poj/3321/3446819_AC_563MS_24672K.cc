#include <iostream>
#include <string>
#define MaxL 100010
using namespace std;

int sum[MaxL]={0},pre[MaxL]={0},n,son[MaxL][50]={0},tp[MaxL]={0};
int a[MaxL]={0}, ord[MaxL]={0}; 
int kk[MaxL]={0},tag[MaxL]={0};
int tot=0,tmp;

void label(int now, int tmp){
	int i,j,k;
	for(i=1;i<=tp[now];i++){
		k=son[now][i];
		if(i==1)
			label(k,tmp);
		else label(k,son[now][i-1]);
	}
	tot++;
	ord[now]=tot;
	pre[now]=tmp;
}

void init(){
	int i,j,k,u,v;
	scanf("%d",&n);
	for(i=1;i<=n;i++) { tag[i]=1;}
	memset(a,0,sizeof a);
	tmp=0;
	for(i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		tp[u]++;
	/*	if(tp[u]>1) pre[v]=son[u][tp[u]-1];
		else{
			if(tmp==0) tmp=v;
			else{
				pre[v]=tmp;
				tmp=v;*/
		son[u][tp[u]]=v;
	}
	label(1,0);
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
		else{
			if(pre[k]!=0)
				printf("%d\n",getsum(ord[k])-getsum(ord[pre[k]]));
			else printf("%d\n",getsum(ord[k]));
		}
				
	}
	
	//for(i=1;i<=n;i++) cout<<ord[i]<<endl;
	//for(i=1;i<=n;i++) cout<<i<<' '<<ord[i]<<endl;
	return 0;
}
