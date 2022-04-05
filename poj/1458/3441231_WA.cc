#include <iostream>
using namespace std;

char s1[501], s2[501];
int f[501][501];

int Max(int a, int b){
	return (a>b)? a : b;
}

void process(){
	int i,j,k;
	memset(f,0,sizeof f);
	if(s1[0]==s2[0]) f[0][0]=1;
	for(i=0;i<strlen(s1);i++)
		for(j=0;j<strlen(s2);j++){
			if(s1[i]==s2[j]){
				if(i==0||j==0)
					f[i][j]=1;
				else
					f[i][j]=f[i-1][j-1]+1;
			}
			else{
				if(i!=0&&j!=0)
					f[i][j]=Max(f[i-1][j], f[i][j-1]);
			}
		}
	cout<<f[strlen(s1)-1][strlen(s2)-1]<<endl;
}

int main(){
	int i,j,k;
	while(cin>>s1>>s2){
		process();
	}
	return 0;
}
