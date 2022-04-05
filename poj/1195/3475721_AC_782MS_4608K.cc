#include <iostream>
#define Max 1040
using namespace std;

int q,n;
int a[Max][Max];

int lowbit(int x){
	return x&(-x);
}

void add(int i, int j, int num){
	int tempj;
	while(i<n+2){
		tempj=j;
		while(tempj<n+2){
			a[i][tempj]+=num;
			tempj+=lowbit(tempj);
		}
		i+=lowbit(i);
	}
}

int sum(int i, int j){
	int tempj,ans=0;
	while(i>0){
		tempj=j;
		while(tempj>0){
			ans+=a[i][tempj];
			tempj-=lowbit(tempj);
		}
		i-=lowbit(i);
	}
	return ans;
}

void init(){
	int i,j,k;
	scanf("%d%d",&i,&n);
	memset(a,0,sizeof a);
}

void process(){
	int i,j,k,x1,x2,y1,y2,n1,save,l1,l2,l3,l4;
	int s;
	while(true){
		scanf("%d",&s);
		if(s==2){
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			printf("%d\n",sum(x2+2,y2+2)-sum(x2+2,y1+1)-sum(x1+1,y2+2)+sum(x1+1,y1+1));
			continue;
		}
		if(s==1){
			scanf("%d%d%d",&x1,&y1,&n1);
			add(x1+2,y1+2,n1);
			continue;
		}
		if(s==3){
			return;
		}
		
	}
}

int main(){
	int i,j,k,t;
//	freopen("1195.in","r",stdin);
		init();
		process();
//	while(k=1);
	return 0;
}
