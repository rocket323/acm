#include <iostream>
#define MaxL 1000000000
using namespace std;

struct node{
	int val;
	int row;
	int p[6];
} nd[200010];

int m,n;
int a[101][2002],len,ans[6],v[4]={0,2,3,5};
int xtmp[6],xt[6];
int px[6];

void swap(int s, int t){
	int tmp;
	
	tmp=nd[s].val; nd[s].val=nd[t].val; nd[t].val=tmp;
	tmp=nd[s].row; nd[s].row=nd[t].row; nd[t].row=tmp;
	memcpy(px, nd[s].p, sizeof nd[s].p);
	memcpy(nd[s].p, nd[t].p, sizeof nd[t].p); 
	memcpy(nd[t].p, px, sizeof px);
}

int deleteMin(){
	int i,j,k,an,t;
	an=nd[1].val;
	nd[1].val=nd[len].val; nd[1].row=nd[len].row;
	memcpy(nd[1].p,nd[len].p,sizeof(nd[len].p));
	len--;
	
	k=1;
	while(k<len){
		i=2*k; j=i+1;
		if(i>len) break;
		if(j>len) t=i;
		else {
			if(nd[i].val<nd[j].val) t=i;
			else t=j;
		}
		if(nd[k].val>nd[t].val){
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
	nd[len].val=ele; nd[len].row=rr;
	memcpy(nd[len].p,xt,sizeof xt);
	k=len;
	while(k>1){
		i=k/2;
		if(nd[k].val<nd[i].val){
			swap(k,i);
			k=i;
		}
		else break;
	}
}

void process(){
	int i,j,k,x,crow;
	len=1;
	nd[1].val=1; nd[1].row=1;
	for(i=1;i<=3;i++){
		nd[1].p[i]=0;
	}
	for(i=1;i<=n;i++){
		memcpy(xtmp,nd[1].p,sizeof(nd[1].p));
		crow=nd[1].row;
		ans[i]=deleteMin();
		
		if(i==n) break;
		for(j=crow;j<=3;j++){
			memcpy(xt,xtmp,sizeof xtmp);
			xt[j]++;
			if(xt[j]>n) continue;
			k=ans[i]*v[j];
			insert(k,j);
		}
	}
	printf("%d\n",ans[n]);
}

int main(){
	int i,j,k,t;
	scanf("%d",&n);
	while(n!=0){
		process();
		scanf("%d",&n);
	}
	return 0;
}
