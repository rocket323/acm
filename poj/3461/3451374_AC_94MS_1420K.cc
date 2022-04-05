#include <iostream>
#define MaxL 1000001
using namespace std;

int n,m,p[MaxL];
char A[MaxL], B[MaxL];

void init(){
	int i,j,k;
	scanf("%s",B); scanf("%s",A);
	n=strlen(A); m=strlen(B);
	p[0]=-1;
	j=-1;
	for(i=1;i<m;i++){
		while(j>-1&&B[j+1]!=B[i]) j=p[j];
		if(B[j+1]==B[i]) j++;
		p[i]=j;
	}
}

void KMP(){
	int i,j,k,match=0;
	j=-1;
	for(i=0;i<n;i++){
		while(j>-1&&B[j+1]!=A[i]) j=p[j];
		if(B[j+1]==A[i]) j++;
		if(j==m-1){
			match++;
			j=p[j];
		}
	}
	printf("%d\n",match);
}

int main(){
	int i,j,k,t;
	scanf("%d",&t);
	for(i=1;i<=t;i++){
		init();
		KMP();
	}
	return 0;
}
	
