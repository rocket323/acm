#include <iostream>
using namespace std;

int g[5][5]={0}, queue[70000][5][5]={0},head,tail,step[70000]={0};
bool used[70000]={0};
int di[4]={-1,0,1,0},dj[4]={0,1,0,-1};

int change(int a[5][5]){
	int i,j,ans=0;
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			ans=ans*2+a[i][j];
	return ans;
}

void init(){
	int i,j,k; char ch;
	head=1; tail=1;
	
	for(i=1;i<=4;i++){
		for(j=1;j<=4;j++){
			cin>>ch;
			if(ch=='b') g[i][j]=1;
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
			if(a[i][j]!=a[1][1])
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
			tmp[i][j]=1-a[i][j];
			for(k=0;k<4;k++){
				ii=i+di[k]; jj=j+dj[k];
				if(ii>0&&ii<=4&&jj>0&&jj<=4)
					tmp[ii][jj]=1-a[ii][jj];
			}
			x=change(tmp);
			
			if(!used[x]){
				tail++;
				memcpy(queue[tail],tmp,sizeof(tmp));
				step[tail]=step[head]+1;
				used[x]=true;
			}
		}
}

void process(){
	int i,j,k;
	while(head<=tail){
		if(check(queue[head])){
			cout<<step[head]<<endl;
			return;
		}
		extend();
		head++;
	}
}

int main(){
	int k;
	init();
	process();
	return 0;
}
