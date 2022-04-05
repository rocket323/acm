#include <iostream>
#define MaxL 1000000000
using namespace std;

struct node{
	int sum;
	int row;
	int p[101];
} nd[200010];

int m,n;
int a[101][2002],len,ans[2001];
int xtmp[101],xt[101];
int px[101];

void swap(int s, int t){
	int tmp;
	
	tmp=nd[s].sum; nd[s].sum=nd[t].sum; nd[t].sum=tmp;
	tmp=nd[s].row; nd[s].row=nd[t].row; nd[t].row=tmp;
	memcpy(px, nd[s].p, sizeof nd[s].p);
	memcpy(nd[s].p, nd[t].p, sizeof nd[t].p); 
	memcpy(nd[t].p, px, sizeof px);
}

int deleteMin(){
	int i,j,k,an,t;
	an=nd[1].sum;
	nd[1].sum=nd[len].sum; nd[1].row=nd[len].row;
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
		if(nd[k].sum>nd[t].sum){
			swap(k,t);
			k=t;
		}
		else break;
	}
	return an;
}

void insert(int ele, int rr){
	int i,j,k;
	len++;
	nd[len].sum=ele; nd[len].row=rr;
	memcpy(nd[len].p,xt,sizeof xt);
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
	int i,j,k,x,crow;
	len=1;
	nd[1].sum=0; nd[1].row=1;
	for(i=1;i<=m;i++){
		nd[1].sum+=a[i][1];
		nd[1].p[i]=1;
	}
	for(i=1;i<=n;i++){
		memcpy(xtmp,nd[1].p,sizeof(nd[1].p));
		crow=nd[1].row;
		ans[i]=deleteMin();
		
		if(i==n) break;
		for(j=crow;j<=m;j++){
			memcpy(xt,xtmp,sizeof xtmp);
			xt[j]++;
			if(xt[j]>n) continue;
			k=ans[i]-a[j][xtmp[j]]+a[j][xt[j]];
			insert(k,j);
		}
	}
}

void out(){
	int i;
	for(i=1;i<n;i++) printf("%d ",ans[i]);
	printf("%d\n",ans[n]);
}

void qsort(int k, int s, int t){
	int i,j,tmp,x;
	x=a[k][(s+t)/2]; i=s; j=t;
	while(i<j){
		while(a[k][i]<x) i++;
		while(a[k][j]>x) j--;
		if(i<=j){
			tmp=a[k][i]; a[k][i]=a[k][j]; a[k][j]=tmp;
			i++; j--;
		}
	}
	if(i<t) qsort(k,i,t);
	if(s<j) qsort(k,s,j);
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
			qsort(i,1,n);
		}
		process();
		out();
	}
	return 0;
}
