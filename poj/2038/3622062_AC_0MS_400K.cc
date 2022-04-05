#include <iostream>
using namespace std;

int N, G[101][7][7], ans[7], A[7], Min, B[7][7];
char s[7];
bool vis[7];

void init(){
	int i,j,k,a,b;
	memset(G,0,sizeof G);
	for(k=1;k<=N;k++){
		scanf("%s",s);
		for(i=0;i<strlen(s)-1;i++)
			for(j=i+1;j<strlen(s);j++){
				a=s[i]-'A'+1; b=s[j]-'A'+1;
				G[k][a][b]=1; G[k][b][a]=-1;
			}
	}
	memset(vis,0,sizeof vis);
	Min=100000000;
}

void refresh(){
	int i,j,k, sum=0;
	memset(B,0,sizeof B);
	for(i=1;i<5;i++)
		for(j=i+1;j<=5;j++){
			B[A[i]][A[j]]=1;
			B[A[j]][A[i]]=-1;
		}
	for(k=1;k<=N;k++){
		for(i=1;i<5;i++)
			for(j=i+1;j<=5;j++)
				if(B[i][j]!=G[k][i][j])
					sum++;
	}
	if(sum<Min){
		memcpy(ans,A,sizeof A);
		Min=sum;
	}
}

void search(int now){
	int i;
	for(i=1;i<=5;i++)
		if(!vis[i]){
			A[now]=i;
			vis[i]=true;
			if(now==5) refresh();
			else search(now+1);
			vis[i]=false;
		}
}

void process(){
	int i,j,k;
	search(1);
	for(i=1;i<=5;i++) printf("%c",ans[i]+'A'-1);
	printf(" is the median ranking with value %d.\n",Min);
}

int main(){
	int i,j,k,a,b;
//	freopen("2038.in","r",stdin);
	scanf("%d",&N);
	while(N!=0){
		init();
		process();
		scanf("%d",&N);
	}
//	while(k=1);
	return 0;
}
