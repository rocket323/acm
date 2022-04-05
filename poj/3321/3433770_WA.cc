#include <iostream>

#define MaxL 100010
using namespace std;

int sum[MaxL]={0},pre[MaxL]={0},n,son[MaxL][3]={0},tp[MaxL]={0};
int a[MaxL]={0};

void build(int now){
	int i,j,k1,k2;
	if(tp[now]==0){ sum[now]=1; return; }
	if(tp[now]==1){
		k1=son[now][1];
		build(k1);
		sum[now]=sum[k1]+1;
		return;
	}
	if(tp[now]==2){
		k1=son[now][1]; k2=son[now][2];
		build(k1); build(k2);
		sum[now]=sum[k1]+sum[k2]+1;
		return;
	}
}

void add(int now,int p){
	int i,j,k;
	if(now==0) return;
	sum[now]+=p;
	add(pre[now],p);
}

int main(){
	int i,j,k,u,v,q,se;
	char ch;
	scanf("%d",&n);
	for(i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		pre[v]=u;
		tp[u]++;
		son[u][tp[u]]=v;
	}
	for(i=1;i<=n;i++) a[i]=1;
	build(1);
	
	scanf("%d",&q);
	for(i=1;i<=q;i++){
		cin>>ch>>k;
		if(ch=='C'){
			if(a[k]==0){
				a[k]==1;
				add(k,1);
			}
			else{
				a[k]=0;
				add(k,-1);
			}
		}
		else printf("%d\n",sum[k]);
	}
	return 0;
}
