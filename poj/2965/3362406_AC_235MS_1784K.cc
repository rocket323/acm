#include <iostream>
using namespace std;

int g[5][5]={0}, queue[70000]={0},head,tail,step[70000]={0},pre[70000]={0},prei[70000]={0},prej[70000]={0};
int move[5][5]={0};
bool used[70000]={0};

int change(int a[5][5]){
	int i,j,ans=0;
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			ans=(ans<<1)+a[i][j];
	return ans;
}

void getMove(){
	int i,j,k;
	int a[5][5]={0};
	for(i=1;i<=4;i++){
		for(j=1;j<=4;j++){
			for(k=1;k<=4;k++){
				a[k][j]=1;
				a[i][k]=1;
			}
			move[i][j]=change(a);
			memset(a,0,sizeof a);
		}
	}
}

void init(){
	int i,j,k; char ch;
	head=1; tail=1;
	
	for(i=1;i<=4;i++){
		for(j=1;j<=4;j++){
			cin>>ch;
			if(ch=='+') g[i][j]=1;
			else g[i][j]=0;
		}
	}
	getMove();
	step[head]=0;
	k=change(g);
	used[k]=1;
	queue[head]=k;
}

void extend(){
	int i,j,k,ii,jj,x;
	int a,tmp;
	
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++){
			x=queue[head]^move[i][j];
			if(!used[x]){
				tail++;
				step[tail]=step[head]+1;
				queue[tail]=x;
				used[x]=true;
				pre[tail]=head;
				prei[tail]=i;
				prej[tail]=j;
			}
		}
}

void out(int x){
	int t;
	if(pre[x]==0) return;
	out(pre[x]);
	cout<<prei[x]<<' '<<prej[x]<<endl;
}

void process(){
	int i,j,k;
	while(head<=tail){
		if(queue[head]==0){
			cout<<step[head]<<endl;
			out(head);
			return;
		}
		extend();
		head++;
	}
	cout<<"Impossible"<<endl;
}

int main(){
	int k;
	init();
	process();
	return 0;
}
