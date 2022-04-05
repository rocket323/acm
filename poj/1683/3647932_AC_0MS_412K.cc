#include <iostream>
using namespace std;

struct node{
	int a, b, c, d;
	char t;
}con[100];

char G[8][8];
int pos[8][8],N,M, P;
bool Find;

void init(){
	int i,j,k,a,b,c,d;
	char ch;
	cin>>M>>N;
	for(i=1;i<=M;i++){
		for(j=1;j<=N;j++){
			cin>>G[i][j];
		}
	}
	cin>>a>>b>>ch>>c>>d; P=0;
	while(a!=0){
		P++;
		con[P].a=a; con[P].b=b; con[P].c=c; con[P].d=d;
		con[P].t=ch;
		cin>>a>>b>>ch>>c>>d;
	}
	memset(pos, 0, sizeof pos);
}

bool check(int man, int item, int i){
	int k;
	for(k=1;k<=P;k++){
		if(con[k].a==item&&con[k].b==i&&pos[con[k].c][con[k].d]!=0){
			if(con[k].t=='N'&&man==pos[con[k].c][con[k].d]) return false;
			if(con[k].t=='R'&&man!=pos[con[k].c][con[k].d]) return false;
		}
		else if(con[k].c==item&&con[k].d==i&&pos[con[k].a][con[k].b]!=0){
			if(con[k].t=='N'&&man==pos[con[k].a][con[k].b]) return false;
			if(con[k].t=='R'&&man!=pos[con[k].a][con[k].b]) return false;
		}
	}
	return true;
}

void out( ){
	int i,j,k;
	for(i=1;i<=N;i++){
		for(j=1;j<=M;j++)
			for(k=1;k<=N;k++)
				if(pos[j][k]==i)
					cout<<G[j][k];
		cout<<endl;
	}
}

void dfs(int man, int item){
	int i,j;
	if(Find) return;
	if(man==N+1){
		Find=true;
		out( );
		return;
	}
	for(i=1;i<=N;i++){
		if(pos[item][i]!=0) continue;
		if(!check(man, item, i)) continue;
		pos[item][i]=man;
		if(item==M) dfs(man+1, 1);
		else dfs(man, item+1);
		pos[item][i]=0;
	}
}

int main(){
	int i,j,k,T;
	cin>>T;
	for(i=1;i<=T;i++){
		Find=false;
		init();
		dfs(1,1);
		cout<<endl;
	}
	return 0;
}
