#include <iostream>
#define MaxL 1000010
using namespace std;

bool vis[2*MaxL+10];
int N, M, Q[2*MaxL+10], st[2*MaxL+10], head, tail;

void move(){
	int i,j,k;
	k=Q[head];
	if(k-1>=0&&vis[k-1]==0){
		tail++;
		vis[k-1]=1;
		Q[tail]=k-1; st[tail]=st[head]+1;
	}
	if(k+1<MaxL&&vis[k+1]==0){
		tail++;
		vis[k+1]=1;
		Q[tail]=k+1; st[tail]=st[head]+1;
	}
	if((2*k)<MaxL&&vis[2*k]==0){
		tail++;
		vis[k*2]=1;
		Q[tail]=2*k; st[tail]=st[head]+1;
	}
}

void process(){
	int i,j,k;
	head=tail=1;
	Q[1]=N; st[1]=0;
	memset(vis, 0, sizeof vis);
	vis[N]=1;
	while(head<=tail){
		if(Q[head]==M){
			cout<<st[head]<<endl;
			return;
		}
		move();
		head++;
	}
}

int main(){
	int i,j,k;
//	freopen("catchcow.3.in", "r", stdin);
//	freopen("oo.out", "w", stdout);
	while(scanf("%d%d", &N, &M)!=EOF){
		process();
	}
//	while(1);
	return 0;
}
