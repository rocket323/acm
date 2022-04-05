#include <iostream>
#define ADD 1000010
using namespace std;

struct node{
	int n, modP;
	int pre, lev, step;
}Q[5*ADD+20];

int N,M,P, head, tail;
bool vis[5*ADD+10];
char S[5]="+-*%";

int Mod( int a, int b){
	int ans;
	ans=a%b;
	if(ans<0) ans+=b;
	return ans;
}

void inqueue(int n, int lev){
	tail++;
	Q[tail].n=n; Q[tail].pre=head;
	Q[tail].lev=lev; Q[tail].step=Q[head].step+1;
	Q[tail].modP=Mod(n, P);
	vis[Mod(n, P)]=true;
}

void out(int k){
	if(Q[k].pre!=0){
		out(Q[k].pre);
		printf("%c",S[Q[k].lev]);
	}
}

void move( ){
	int i,j,k, a, b;
	a=Q[head].n;
	
	b=a+M;
	if(!vis[Mod(b, P)]) inqueue(b, 0);
	
	b=a-M;
	if(!vis[Mod(b, P)]) inqueue(b, 1);
	
	b=a*M;
	if(!vis[Mod(b, P)]) inqueue(b, 2);
	
	b=Mod(a, M);
	if(!vis[Mod(b, P)]) inqueue(b, 3);
}

void process(){
	int i,j,k;
	memset(vis, 0, sizeof vis);
	head=1; tail=1;
	Q[head].n=N; Q[1].pre=0; Q[1].lev=0; Q[1].step=0; Q[1].modP=Mod(N,P);
	vis[Mod(N, P)]=true;
	while(head<=tail){
		if(Mod(Q[head].n, P)==Mod(N+1, P)){
			printf("%d\n",Q[head].step);
			out(head);
			printf("\n");
			return;
		}
		move( );
		head++;
	}
	printf("0\n");
}

int main(){
	int i,j,k;
//	freopen("2426.in","r",stdin);
//	freopen("2426.out","w",stdout);
	scanf("%d%d%d",&N,&P,&M);
	while(!(N==0&&M==0&&P==0)){
		process();
		scanf("%d%d%d",&N,&M,&P);
	}
//	while(k=1);
	return 0;
}
