#include <iostream>
#define Max 100000000
using namespace std;

int TM,g[101][101],n,m,d[101],c[101],l[101][101],t[101][101];
int num[101]={0},len=0;
int nod[1000001],mon[1000001], path[1000001],curm=0;
bool flag=false;

void swap(int i, int j){
	int tmp;
	tmp=nod[i]; nod[i]=nod[j]; nod[j]=tmp;
	tmp=mon[i]; mon[i]=mon[j]; mon[j]=tmp;
	tmp=path[i]; path[i]=path[j]; path[j]=tmp;
}

void add(int cn, int cp, int cm){
	len++;
	nod[len]=cn; path[len]=cp; mon[len]=cm;
	int i,j,k,mid;
	k=len;
	while(k>1){
		mid=k>>1;
		if(path[k]<path[mid]){
			swap(k, mid);
			k=mid;
		}
		else break;
	}
}

void del(){
	int i,j,k,tmp;
	swap(1, len);
	len--;
	k=1;
	while(k<len){
		i=2*k; j=i+1;
		if(i>len) break;
		if(j>len) tmp=i;
		else {
			if(path[i]<path[j]) tmp=i;
			else tmp=j;
		}
		if(path[k]>path[tmp]){
			swap(k, tmp);
			k=tmp;
		}
		else break;
	}
}

void init(){
	int i,j,k,a,b,x,y;
	scanf("%d%d%d",&TM,&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d%d%d%d",&a,&b,&x,&y);
		num[a]++;
		g[a][num[a]]=b;
		l[a][num[a]]=x;
		t[a][num[a]]=y;
	}
	add(1, 0, 0);
}

void process(){
	int i,j,k,tmp,cn,cm,cp,MM;
	while(true){
		if(len==0){ cout<<"-1"<<endl; return; }
		cn=nod[1]; cm=mon[1]; cp=path[1];
		if(cn==n) { cout<<cp<<endl; return; }
		d[cn]=1; c[cn]=cm;
		del();	
		for(i=1;i<=num[cn];i++){
			tmp=g[cn][i]; MM=cm+t[cn][i];
			if(!d[tmp]||(d[tmp]&&c[tmp]>MM))
				if(MM<=TM){
					d[tmp]=0;
					add(tmp, cp+l[cn][i], MM);
				}
		}
	}
}	

int main(){
	int i,j,k;
	//freopen("1724.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
