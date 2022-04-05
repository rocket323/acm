#include <iostream>
#include <cmath>
#define Prime 65535
#define MaxN 100010
using namespace std;

struct Node{
	int idx;
	Node *next;
};
Node head[Prime+10], memo[5*Prime];

int N, M, S[MaxN][31], ans, mset;

void init(){
	int i,j,k,p;
	scanf("%d%d", &N, &M);
	memset(S, 0, sizeof S);
	for(i=1; i<=N; ++i){
		scanf("%d", &p);
		for(j=0; j<M; ++j) S[i][j]=S[i-1][j];
		for(j=0; (1<<j)<=p; ++j){
			if(p&(1<<j)) S[i][j]++;
		}
	}
	
	
	mset=0; ans=0;
	for(i=0; i<Prime; ++i) head[i].next=NULL;
}

void insert(int idx, int num){
	Node* ptr=&memo[mset++];
	ptr->idx=idx;
	ptr->next=head[num].next;
	head[num].next=ptr;
}

void hash(int idx){
	int tmp=0, i, id;
	bool flag;
	for(i=1; i<M; ++i) tmp+=(S[idx][i]-S[idx][0]);
	tmp=abs(tmp)%Prime;
	Node *ptr=head[tmp].next;
	
	while(ptr){
		id=ptr->idx;
		flag=1;
		for(i=1; i<M; i++)
			if(S[idx][i]-S[id][i]!=S[idx][i-1]-S[id][i-1]){
				flag=0;
				break;
			}
		if(flag){
			if(idx-id>ans) ans=idx-id;
			return;
		}
		ptr=ptr->next;
	}
	insert(idx, tmp);
}

void process(){
	int i,j,k;
	
	hash(0);
	for(i=1; i<=N; ++i){
		hash(i);
	}
	printf("%d\n", ans);
}

int main(){
	int i,j,k;
	init();
	process();
	return 0;
}
