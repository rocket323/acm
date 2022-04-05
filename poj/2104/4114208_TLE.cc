#include <iostream>

#include <algorithm>

#define MaxN 100010

#define MaxL 6553573

using namespace std;



struct Treap{

    int size, pri, key;

    Treap *left;

    Treap *right;

};



struct node{

    int l, r;

    Treap *root;

}nd[4*MaxN];



Treap *nullNode;



int A[MaxN], B[MaxN], N, M;



void update(Treap *now){ now->size=now->left->size + now->right->size + 1; }



void rotateWithLeftChild(Treap * & now){

	Treap *k=now->left;

	now->left=k->right; update(now);

	k->right=now; update(k);

	now=k;

}



void rotateWithRightChild(Treap * & now){

	Treap *k=now->right;

	now->right=k->left; update(now);

	k->left=now; update(k);

	now=k;

}



void addNode(Treap *& now, int key, Treap *& l, Treap *& r, int pri){

	Treap *newNode=new Treap;

	newNode->left=l; newNode->right=r;

	newNode->pri=pri;

	newNode->key=key; newNode->size=1;

	now=newNode;

}



void insert(Treap * & now, int x){

    if(now==nullNode){

        addNode(now, x, nullNode, nullNode, rand());

    }

    else if(x<now->key){

        insert(now->left, x);

        ++now->size;

        if(now->left->pri<now->pri)

            rotateWithLeftChild(now);

    }

    else if(x>now->key){

        insert(now->right, x);

        ++now->size;

        if(now->right->pri<now->pri)

            rotateWithRightChild(now);

    }

}



int rank(Treap * & now, int x){

	if(now==nullNode) return 0;

	if(x==now->key) return now->left->size + 1;

	if(x<now->key) return rank(now->left, x);

	return now->left->size + 1 + rank(now->right, x);

}



void build(int now, int a, int b){

    nd[now].l=a; nd[now].r=b;

    nd[now].root=nullNode;

    for(int i=a; i<=b; ++i){ 

		insert(nd[now].root, A[i]);

//		cout<<i<<' ';

	}

//	cout<<endl;

    if(a<b){

        int mid=(a+b)>>1;

        build(now<<1, a, mid);

        build((now<<1)+1, mid+1, b);

    }

}



int getRank(int now, int x, int l, int r){

    if(l<=nd[now].l&&nd[now].r<=r) return rank(nd[now].root, x);

    int mid=(nd[now].l+nd[now].r)>>1;

    int lv=0, rv=0;

    if(l<=mid) lv=getRank(now*2, x, l, r);

    if(r>mid) rv=getRank(now*2+1, x, l, r);

    return lv+rv;

}   



int getK_th(int a, int b, int K){

    int i,j, res, l=1, r=N, mid;

    while(l<=r){

        mid=(l+r)>>1;

        i=getRank(1, B[mid], a, b);

        if(i>=K){

            if(i==K) res=mid;

            r=mid-1;

        }

        else l=mid+1;

    }

    return B[res];   

}



void init(){

    int i,j,k;

    for(i=1; i<=N; ++i){ scanf("%d", &A[i]); B[i]=A[i]; }

    sort(B+1, B+1+N);

    build(1, 1, N);

}



void process(){

    int a, b, i,j,K, res;

    for(i=1; i<=M; ++i){

        scanf("%d%d%d", &a, &b, &K);

        res=getK_th(a, b, K);

        printf("%d\n", res);

    }

}



int main(){

//	freopen("2104.in", "r", stdin);

 //   freopen("kth.in", "r", stdin);

  //  freopen("kth.out", "w", stdout);

    scanf("%d%d", &N, &M);

    nullNode=new Treap;

    nullNode->size=0;

    init();

    process();

//    while(1);

    return 0;

}


