#include <iostream>
#define MaxL 100000000
using namespace std;

struct node{
	int sum;
	int p[101];
} nd[15000];

int m,n;
int a[101][2002],len,ans[2001],xtmp[101],xt[101];

void swap(int s, int t){
	int tmp, x[101];
	tmp=nd[s].sum; nd[s].sum=nd[t].sum; nd[t].sum=tmp;
	memcpy(x, nd[s].p, sizeof nd[s].p);
	memcpy(nd[s].p, nd[t].p, sizeof nd[t].p); 
	memcpy(nd[t].p, x, sizeof x);
}

int deleteMin(){
	int i,j,k,an,t;
	an=nd[1].sum;
	nd[1].sum=nd[len].sum;
	memcpy(nd[1].p,nd[len].p,sizeof(nd[len].p));
	len--;
	
	k=1;
	while(k<len){
		i=2*k; j=i+1;
		if(i>len) break;
		if(j>len) t=i;
		else {
			if(nd[i].sum<nd[j].sum) t=i;
			else t=j;
		}
		swap(k,t);
		k=t;
	}
	return an;
}

void insert(int ele,int t[]){
	int i,j,k;
	len++;
	nd[len].sum=ele;
	memcpy(nd[len].p,t,sizeof t);
	k=len;
	while(k>1){
		i=k/2;
		if(nd[k].sum<nd[i].sum){
			swap(k,i);
			k=i;
		}
		else break;
	}
}

void process(){
	int i,j,k;
	nd[1].sum=0;
	for(i=1;i<=m;i++){
		nd[1].sum+=a[i][1];
		nd[1].p[i]=1;
	}
	for(i=1;i<=n;i++){
		memcpy(xtmp,nd[1].p,sizeof(nd[1].p));
		ans[i]=deleteMin();
		
		if(i==n) break;
		for(j=1;j<=m;j++){
			memcpy(xt,xtmp,sizeof xtmp);
			xt[j]++;
			k=ans[i]-a[j][xtmp[j]]+a[j][xt[j]];
			insert(k,xt);
		}
	}
}

void out(){
	int i;
	for(i=1;i<n;i++) printf("%d ",ans[i]);
	printf("%d\n",ans[n]);
}

int main(){
	int i,j,k,t;
	scanf("%d",&t);
	for(k=1;k<=t;k++){
		len=0;
		scanf("%d%d",&m,&n);
		for(i=1;i<=m;i++){
			for(j=1;j<=n;j++)
				scanf("%d",&a[i][j]);
			a[i][n+1]=MaxL;
		}
		process();
		out();
	}
	return 0;
}
