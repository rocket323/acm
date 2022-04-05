#include <iostream>
#define Mod 10000
using namespace std;

int n,p[3][3]={0,0,0,0,1,1,0,1,0},ans[3][3];

void MatrixMul(int a[3][3],int b[3][3], int c[3][3]){
	int i,j,k;
	for(i=1;i<=2;i++)
		for(j=1;j<=2;j++){
			a[i][j]=0;
			for(k=1;k<=2;k++)
				a[i][j]+=(b[i][k]*c[k][j])%Mod;
		}
}

void Mat(int t[3][3],int x){
	int i,j,k,mid=x/2; 
	int tmp[3][3];
	if(x==1){
		memcpy(t,p,sizeof p);
		return;
	}
	Mat(t,mid);
	MatrixMul(tmp,t,t);
	if(x%2==1){
		MatrixMul(t,tmp,p);
		return;
	}
	memcpy(t,tmp,sizeof tmp);
}

void process(){
	int i,j,k;
	if(n==0){
		cout<<0<<endl;
		return;
	}
	Mat(ans,n);
	cout<<ans[1][2]%Mod<<endl;
}

int main(){
	int i,j,k;
	cin>>n;
	while(n!=-1){
		process();
		cin>>n;
	}
	return 0;
}
	
