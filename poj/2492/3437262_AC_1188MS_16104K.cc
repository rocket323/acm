#include <iostream>
using namespace std;

int n,m,col[2001],g[2001][2001];
int num[2001];
bool flag;

void flood(int x,int c){
	int i,k;
	
	col[x]=c;
	for(i=1;i<=num[x];i++){
		k=g[x][i];
		if(col[k]==0){
			if(c==1) flood(k,2);
			else flood(k,1);
		}
		else{
			if(col[k]==c){
				flag=false;
				return;
			}	
		}
	}
}

void process(int x){
	int i,j,k,a,b;
	memset(num,0,sizeof num);
	memset(col,0,sizeof col);
	for(i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		num[a]++; num[b]++;
		g[a][num[a]]=b; g[b][num[b]]=a;
	}
	for(i=1;i<=n;i++)
		if(col[i]==0){
			flag=true;
			flood(i,1);
			if(!flag){
				printf("Scenario #%d:\n",x);
				printf("Suspicious bugs found!\n\n");
				return;
			}
		}
	printf("Scenario #%d:\n",x);
	printf("No suspicious bugs found!\n\n");
				
}

int main(){
	int i,j,k,t;
	scanf("%d",&t);
	for(i=1;i<=t;i++){
		scanf("%d%d",&n,&m);
		process(i);
	}
	return 0;
}
