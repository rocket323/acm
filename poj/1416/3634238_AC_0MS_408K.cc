#include <iostream>
using namespace std;

char S[8];
int tar, num[8][8], Len, Max, cnt;
int A[10], tp, St[10];

void init(){
	int i,j,k,ans;
	Len=strlen(S);
	Max=-1; cnt=0; tp=0;
	for(i=1;i<=strlen(S);i++)
		for(j=i;j<=strlen(S);j++){
			ans=0;
			for(k=i-1;k<=j-1;k++)
				ans=ans*10+(S[k]-'0');
			num[i][j]=ans;
		}
}

void save( ){
	int i,j,k;
	St[0]=tp;
	for(i=1;i<=tp;i++) St[i]=A[i];
}

void dfs(int lstP, int sum){
	int i,j,k;
	if(lstP==Len) {
		if(sum<=tar){
			if(sum==Max) cnt=2;
			else if(sum>Max){
				Max=sum;
				cnt=1;
				save( );
			}
		}
	}
	for(i=lstP+1; i<=Len; i++){
		tp++;
		A[tp]=num[lstP+1][i];
		dfs(i, sum+num[lstP+1][i]);
		tp--;
	}
}

void out( ){
	int i;
	printf("%d ",Max);
	for(i=1;i<St[0]; i++) printf("%d ",St[i]);
	printf("%d\n",St[St[0]]);
}

int main(){
	int i,j,k;
//	freopen("1416.in","r",stdin);
	cin>>tar>>S;
	while(tar!=0){
		init();
		if(tar==num[1][Len]){
			printf("%d %d\n",tar,tar);
		}
		else{
			dfs(0, 0);
			if(Max==-1) printf("error\n");
			else if(cnt==2) printf("rejected\n");
			else out( );
		}
		cin>>tar>>S;
	}
//	while(k=1);
	return 0;
}
