#include <iostream>;
using namespace std;
/*这是我写的一个关于线段树的样例，题目来源 : Ural1037挑内存*/


struct node{
	long minTime;
	long a,b;
	node *left;
	node *right;
};
node *root;
long ttime,n,i,j,k;
long lastTime[40000]={0};

void build(node *x,long l,long r){
	long k;
	x->a=l; x->b=r;
	x->minTime=0;
	if(r-l>=1){
		k=(l+r)/2;
		x->left=new node;
		build(x->left,l,k);
		x->right=new node;
		build(x->right,k+1,r);
	}
	else{
		x->left=NULL;
		x->right=NULL;
	}
}

long minM(long a,long b){
	if(a<b) return a;
	else return b;
}

void update(node *x){
	if(x->b>x->a)
		x->minTime=minM(x->left->minTime,x->right->minTime);
}

long search(node *x,long ttime){
	long k;
	if(x->minTime==0||x->minTime<=ttime-600){
		if(x->a==x->b) {lastTime[x->a]=ttime; x->minTime=ttime; k=x->a;}
		else if(x->left->minTime==0||x->left->minTime<=ttime-600)
					k=search(x->left,ttime);
			 else if(x->right->minTime==0||x->right->minTime<=ttime-600)
			 		k=search(x->right,ttime);
		update(x);
		return k;
	}
	else return 0;
}

void look(node *x,long ttime,long load){
	long k;
	k=(x->a+x->b)/2;
	if(x->a==x->b&&x->a==load){
		if((ttime-lastTime[load])>=600||lastTime[load]==0) cout<<'-'<<endl;
		else {
				cout<<'+'<<endl;
				lastTime[load]=ttime;
				x->minTime=ttime;
		}
	}
	else if(load<=k) look(x->left,ttime,load);
	else look(x->right,ttime,load);
	update(x);
}

void processVisit(long ttime, long load){
	look(root,ttime,load);
}

void processRequest(long ttime){
	long k;
	
	k=search(root,ttime);
	if(k==0)
		cout<<'-'<<endl;
	else cout<<k<<endl;
}

int main(){
 	char ch;
	long load;
	//freopen("memo7.in","r",stdin);
//	freopen("ans.txt","w",stdout);
	root=new node;
	build(root,1,30000);
	while(cin>>ttime){
		cin>>ch;
		if(ch=='.'){
			cin>>load;
			processVisit(ttime,load);
		}
		else
			processRequest(ttime);
	}
//	cout<<"end."<<endl;
	return 0;
}
			
