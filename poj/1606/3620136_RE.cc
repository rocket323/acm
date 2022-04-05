#include <iostream>
using namespace std;

struct node{
	int fa,fb;
	int pre, opt;
}Q[1000010];

int ca, cb, N, head ,tail;
int vis[1001][1001];
char S[6][27]={"fill A","fill B","empty A","empty B","pour A B","pour B A"};

int Min(int a, int b){
	return(a<b)?a:b;
}

void out(int now){
	if(Q[now].pre!=0){
		out(Q[now].pre);
		printf("%s\n",S[Q[now].opt]);
	}
}

void init(){
	int i,j,k;
	head=1; tail=1;
	Q[1].fa=0; Q[1].fb=0; Q[1].pre=0; Q[1].opt=0;
	memset(vis,0,sizeof vis);
	vis[0][0]=true;
}

void work0(){
	if(Q[head].fa<ca){
		tail++;
		Q[tail].fa=ca; Q[tail].fb=Q[head].fb; Q[tail].pre=head;
		Q[tail].opt=0;
	}
}

void work1(){
	if(Q[head].fb<cb){
		tail++;
		Q[tail].fa=Q[head].fa; Q[tail].fb=cb; Q[tail].pre=head;
		Q[tail].opt=1;
	}
}

void work2(){
	if(Q[head].fa>0){
		tail++;
		Q[tail].fa=0; Q[tail].fb=Q[head].fb; Q[tail].pre=head;
		Q[tail].opt=2;
	}
}

void work3(){
	if(Q[head].fb>0){
		tail++;
		Q[tail].fa=Q[head].fa; Q[tail].fb=0; Q[tail].pre=head;
		Q[tail].opt=3;
	}
}

void work4(){
	if(Q[head].fa>0&&Q[head].fb<cb){
		int k=Min(Q[head].fa, cb-Q[head].fb);
		tail++;
		Q[tail].fa=Q[head].fa-k; Q[tail].fb=Q[head].fb+k; Q[tail].pre=head;
		Q[tail].opt=4;
	}
}

void work5(){
	if(Q[head].fb>0&&Q[head].fa<ca){
		int k=Min(Q[head].fb, ca-Q[head].fa);
		tail++;
		Q[tail].fb=Q[head].fb-k; Q[tail].fa=Q[head].fa+k; Q[tail].pre=head;
		Q[tail].opt=5;
	}
}

void operate(){
	int i,j,k;
	for(i=0;i<6;i++){
		switch (i){
			case 0: work0(); break;
			case 1: work1(); break;
			case 2: work2(); break;
			case 3: work3(); break;
			case 4: work4(); break;
			case 5: work5(); break;
		}
	}
}

void process(){
	int i,j,k;
	while(head<=tail){
		if(Q[head].fb==N){
			out(head);
			printf("success\n");
			return;
		}
		operate();
		head++;
	}
}
		
int main(){
	int i,j,k;
//	freopen("1606.in","r",stdin);
	while(scanf("%d%d%d",&ca,&cb,&N)!=EOF){
		init();
		process();
	}
//	while(k=1);
	return 0;
}
