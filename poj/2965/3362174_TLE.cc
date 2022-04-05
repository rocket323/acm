#include <iostream>
using namespace std;

int g[5][5]={0}, queue[70000][5][5]={0},head,tail,step[70000]={0},pre[70000]={0},prei[70000]={0},prej[70000]={0};
bool used[70000]={0};

int change(int a[5][5]){
	int i,j,ans=0;
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			ans=(ans<<1)+a[i][j];
	return ans;
}

void init(){
	int i,j,k; char ch;
	head=1; tail=1;
	
	for(i=1;i<=4;i++){
		for(j=1;j<=4;j++){
			cin>>ch;
			if(ch=='+') g[i][j]=1;
			else g[i][j]=0;
			queue[head][i][j]=g[i][j];
		}
	}
	
	step[head]=0;
	k=change(queue[head]);
	used[k]=1;
}

bool check(int a[5][5]){
	int i,j;
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			if(a[i][j]!=0)
				return false;
	return true;
}

void extend(){
	int i,j,k,ii,jj,x;
	int a[5][5],tmp[5][5];
	memcpy(a,queue[head],sizeof(queue[head]));
	
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++){
			memcpy(tmp,a,sizeof(a));
			for(k=1;k<=4;k++) tmp[i][k]=a[i][k]^1;
			for(k=1;k<=4;k++) tmp[k][j]=a[k][j]^1;
			
			tmp[i][j]=a[i][j]^1;
			
			x=change(tmp);
			if(!used[x]){
				tail++;
				memcpy(queue[tail],tmp,sizeof(tmp));
				step[tail]=step[head]+1;
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
		if(check(queue[head])){
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
//	freopen("2965.in","r",stdin);
	int k;
	init();
	process();
//	while(k=1);
	return 0;
}
