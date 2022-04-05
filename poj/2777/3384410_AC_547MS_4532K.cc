#include <iostream>
#include <string>
#define MaxL 100010
using namespace std;

struct node{
	int l,r;
	int fresh;
	int col;
} nd[4*MaxL];

int l,t,op;

void build(int now, int a, int b){
	nd[now].l=a; nd[now].r=b;
	nd[now].fresh=0; nd[now].col=1;
	if(b>a){
		int mid=(a+b)>>1;
		build(now*2,a,mid);
		build(now*2+1,mid+1,b);
	}
}

void clear(int now){
	nd[now].fresh=0;
	nd[now*2].fresh=-1;
	nd[now*2+1].fresh=-1;
	nd[now*2].col=nd[now].col;
	nd[now*2+1].col=nd[now].col;
}

void insert(int now, int a, int b, int val){
	if(a<=nd[now].l&&nd[now].r<=b){
		nd[now].col=val;
		if(nd[now].l!=nd[now].r)
			nd[now].fresh=-1;
		return;
	}
	if(nd[now].fresh==-1) clear(now);
	
	int mid=(nd[now].l+nd[now].r)>>1;
	if(a<=mid) insert(now*2,a,b,val);
	if(b>mid) insert(now*2+1,a,b,val);
	nd[now].col=nd[now*2].col | nd[now*2+1].col;
}

int getTree(int now, int a, int b){
	if(a<=nd[now].l&&nd[now].r<=b)
		return nd[now].col;
	int lc=0,rc=0,ans=0;
	int mid=(nd[now].l+nd[now].r)>>1;
	
	if(nd[now].fresh==-1) clear(now);
	
	if(a<=mid)
		lc=getTree(now*2,a,b);
	if(b>mid)
		rc=getTree(now*2+1,a,b);
	ans=lc|rc;
	return ans;
}

int process(int x){
	int i,k,cnt=0;
	while(x>0){
		k=x%2;
		if(k==1) cnt++;
		x=x/2;
	}
	return cnt;
}

int main(){
	int i,k,a,b,c,tmp,xx; char ch;
	char s[20];
	//freopen("2777.in","r",stdin);
	//scanf("%d%d%d",&l,&t,&op);
	cin>>l>>t>>op;
	build(1,1,l);
	for(i=1;i<=op;i++){
		//gets(s);
		cin>>ch;
		//cout<<ch<<endl;
		//cin>>ch;
		if(ch=='C'){
			scanf("%d%d%d",&a,&b,&c);
			if(a>b){ xx=a; a=b; b=xx; }
			//cin>>a>>b>>c;
			tmp=1<<(c-1);
			//insert(1,s[2]-'0',s[4]-'0',tmp);
			insert(1,a,b,tmp);
		}
		
		else if(ch=='P'){
			scanf("%d%d",&a,&b);
			if(a>b){ xx=a; a=b; b=xx; }
			//cin>>a>>b;
			//k=getTree(1,s[2]-'0',s[4]-'0');
			k=getTree(1,a,b);
			printf("%d\n",process(k));
		}
	}
	//while(k=1);
	return 0;
}
