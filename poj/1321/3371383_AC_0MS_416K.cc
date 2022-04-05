#include <iostream>
using namespace std;

int n,knt,tot;
bool r[9],c[9],g[9][9];

void init(){
	int i,j,k;
	char ch;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++){
			cin>>ch;
			if(ch=='#') g[i][j]=1;
			else g[i][j]=0;
		}
}

void search(int x,int place){
	int i,j,k;
	if(place==knt){
		tot++;
		return;
	}
	if(x>n) return;
	if(n-x+1+place<knt) return;
	for(i=1;i<=n;i++){
		if(!c[i]&&g[x][i]){
			c[i]=true;
			search(x+1,place+1);
			c[i]=false;
			
		}
	}
	search(x+1,place);
}

void process(){
	int i,j,k;
	tot=0;
	memset(c,0,sizeof c);
	search(1,0);
	cout<<tot<<endl;
}

int main(){
	int k;
	cin>>n>>knt;
	while(n!=-1){
		init();
		process();
		cin>>n>>knt;
	}
	return 0;
}
