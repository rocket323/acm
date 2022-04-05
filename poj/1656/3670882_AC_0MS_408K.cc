#include <iostream>
using namespace std;

int N, x, y, l, A[101][101];
char s[7];

void init(){
	int i,j,k;
	memset(A, 0, sizeof A);
}

void process(){
	int i,j,k,a ,b,ans;
	scanf("%d",&k);
	for(i=1;i<=k;i++){
		scanf("%s%d%d%d",s,&x,&y,&l);
		if(s[0]=='B'){
			for(a=x;a<x+l;a++)
				for(b=y;b<y+l;b++)
					A[a][b]=1;
		}
		else if(s[0]=='W'){
			for(a=x;a<x+l;a++)
				for(b=y;b<y+l;b++)
					A[a][b]=0;
		}
		else if(s[0]=='T'){
			ans=0;
			for(a=x;a<x+l;a++)
				for(b=y;b<y+l;b++)
					if(A[a][b]==1)
						ans++;
			printf("%d\n",ans);
		}
	}
}		

int main(){
	int i, j, k;
//	 freopen("1656.in","r",stdin);
	 init();
	 process();
//	 while(k=1);
	 return 0;
}
