#include <iostream>
#define QLen 1000000
using namespace std;

struct node{
	int pre, label;
	int sta[9];
}Q[QLen+10];

int move[9][5]={0,1,3,4,0,
				0,1,2,0,0,
				1,2,4,5,0,
				0,3,6,0,0,
				1,3,4,5,7,
				2,5,8,0,0,
				3,4,6,7,0,
				6,7,8,0,0,
				4,5,7,8,0},
	l[9]={4,3,4,3,5,3,4,3,4};
int head, tail;
bool vis[2000000];
int st[2000000], tp;

bool unvisited(int A[]){
	int ans=0,i,j,k;
	for(i=0;i<9;i++){
		ans=ans*4+A[i];
	}
	if(!vis[ans]){
		vis[ans]=true;
		return true;
	}
	return false;
}

void init(){
	int i,j,k;
	head=1; tail=1;
	memset(vis,0,sizeof vis);
	for(i=0;i<9;i++)
		scanf("%d",&Q[1].sta[i]);
	Q[1].pre=0; Q[1].label=0;
	if(unvisited(Q[1].sta)){};
}

bool check(int A[]){
	for(int i=0;i<9;i++)
		if(A[i]!=0)
			return false;
	return true;
}

void makeMove(){
	int i,j,k;
	int tmp[9];
	for(i=0;i<9;i++){
		memcpy(tmp, Q[head].sta, sizeof(Q[head].sta));
		for(j=0;j<l[i];j++){
			tmp[move[i][j]]++;
			if(tmp[move[i][j]]==4) tmp[move[i][j]]=0;
		}
		if(unvisited(tmp)){
			tail++;
			Q[tail].pre=head;
			Q[tail].label=i+1;
			memcpy(Q[tail].sta, tmp, sizeof tmp);
		}
	}
}

void out(){
	int i,j,k;
	k=head; tp=0;
	while(Q[k].pre!=0){
		tp++; st[tp]=Q[k].label;
		k=Q[k].pre;
	}
	for(i=tp;i>1;i--) printf("%d ",st[i]);
	printf("%d\n",st[1]);
}

void process(){
	int i,j,k;
	while(head<=tail){
		if(check(Q[head].sta)) out();
		makeMove();
		head++;
	}
}	

int main(){
	int i,j,k;
//	freopen("1166.in","r",stdin);
	init();
	process();
	
//	while(k=1);
	return 0;
}
	
