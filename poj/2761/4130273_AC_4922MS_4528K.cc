#include <iostream>
#include <algorithm>
#include <time.h>
#define MaxN 100010
#define MaxM 50010
#define Mod 655367
using namespace std;

struct Treap{
	int key, pri, size, cnt;
	Treap *left;
	Treap *right;
};

Treap *root, *nullNode, memo[40*MaxN];

struct query{
	int a, b, K;
	int id, res;
}Q[MaxM];

struct seg{
	int a, b;
};

int N, M, A[MaxN], B[MaxN], mset;
bool del;
bool flag=0;

bool cmp(const query &A, const query &B){
	return (A.a<B.a);
}

bool cmp2(const query &A, const query &B){
	return (A.id<B.id);
}

void addNullNode(){
	nullNode=new Treap;
	nullNode->size=0; nullNode->cnt=0; nullNode->key=0;
	nullNode->left=nullNode->right=nullNode;
	nullNode->pri=Mod+1;
	root=nullNode;
}

void init(){
	int i,j,k;
	scanf("%d%d", &N, &M);
	mset=0;
	addNullNode();
	for(i=1; i<=N; ++i){ scanf("%d", &A[i]); B[i]=A[i]; }
	sort(B+1, B+1+N);
	for(i=1; i<=M; ++i){
		scanf("%d%d%d", &Q[i].a, &Q[i].b, &Q[i].K);
		if(Q[i].a>Q[i].b){ int tmp=Q[i].a; Q[i].a=Q[i].b; Q[i].b=tmp; }
		Q[i].id=i;
	}
	sort(Q+1, Q+1+M, cmp);
}

void update(Treap *& now){
	if(now==nullNode) return;
	now->size = now->left->size + now->right->size + now->cnt;
}

void rotateRight(Treap *& now){
	Treap *k=now->left;
	now->left=k->right; update(now);
	k->right=now; update(k);
	now=k;
}

void rotateLeft(Treap *& now){
	Treap *k=now->right;
	now->right=k->left; update(now);
	k->left=now; update(k);
	now=k;
}

void addNode(Treap *& now, Treap *l, Treap *r, int pri, int key){
	Treap *newNode=&memo[mset++];
	newNode->left=l; newNode->right=r;
	newNode->pri=pri;
	newNode->key=key; newNode->size=1; newNode->cnt=1;
	now=newNode;
}

void insert(Treap *& now, int key){
	if(now==nullNode){
		addNode(now, nullNode, nullNode, rand()%Mod, key);
		return;
	}
	
	if(key<now->key){
		insert(now->left, key);
		++now->size;
		if(now->left->pri<now->pri) rotateRight(now);
	}
	else if(key>now->key){
		insert(now->right, key);
		++now->size;
		if(now->right->pri<now->pri) rotateLeft(now);
	}
	else{ ++now->size; ++now->cnt; }
}

void remove(Treap *& now, int key){
	if(now==nullNode) return;
	if(key<now->key){ remove(now->left, key); --now->size; }
	else if(key>now->key){ remove(now->right, key); --now->size; }
	else {
		if(now->cnt>1){ --now->size; --now->cnt; return; }
		if(now->left->pri<now->right->pri) rotateRight(now);
		else rotateLeft(now);
		if(now!=nullNode) remove(now, key);
		else now->left=nullNode;
	}
}

seg rank(Treap *& now, int key){
	seg msg, tmp;
	if(now==nullNode){
		msg.a=msg.b=1;
		return msg;
	}
	if(key==now->key){
		msg.a=now->left->size + 1;
		msg.b=msg.a + now->cnt - 1;
		return msg;
	}
	if(key<now->key) return rank(now->left, key);
	tmp=rank(now->right, key);
	msg.a=tmp.a + now->left->size + now->cnt;
	msg.b=tmp.b + now->left->size + now->cnt;
	return msg;
}

int getRank(int rk){
	int k, l, r, mid, res=-MaxN;
	seg msg;
	l=1; r=N;
	while(l<=r){
		int mid=(l+r)>>1;
		msg=rank(root, B[mid]);
		if(msg.a<=rk&&rk<=msg.b) res=mid;
		if(rk<msg.a) r=mid-1;
		else l=mid+1;
	}
	return B[res];
}


int Max(int a, int b){
	return (a>b)?a:b;
}

int Min(int a, int b){
	return (a<b)?a:b;
}

void process(){
	int i,j,k, s, t;
	for(i=Q[1].a; i<=Q[1].b; ++i) insert(root, A[i]);
	Q[1].res=getRank(Q[1].K);

	for(i=2; i<=M; ++i){
		t=Min(Q[i-1].b, Q[i].b);
		s=Max(Q[i-1].a, Q[i].a);
		if(s<=t){
			for(j=Q[i-1].a; j<s; ++j){ del=0; remove(root, A[j]); }
			for(j=Q[i-1].b+1; j<=Q[i].b; ++j){ insert(root, A[j]); }
		}
		else{
			for(j=Q[i-1].a; j<=Q[i-1].b; ++j) { del=0; remove(root, A[j]); }
			for(j=Q[i].a; j<=Q[i].b; ++j){ insert(root, A[j]); }
		}

	
		Q[i].res=getRank(Q[i].K);
	}

	
	sort(Q+1, Q+1+M, cmp2);
	for(i=1; i<=M; ++i) printf("%d\n", Q[i].res);
}

int main(){
	int i;
	init();
	process();
	return 0;
}
