#include <iostream>
using namespace std;

int n,m,w[101],p[101];
char s[101][52];

void init(){
	int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
		scanf("%s",s[i]);
	for(k=1;k<=m;k++){
		w[k]=0;
		for(i=0;i<n-1;i++)
			for(j=i+1;j<=n-1;j++)
				if(s[k][i]>s[k][j])
					w[k]++;
	}
}

void process(){
	int i,j,k,tmp;
	for(i=1;i<=m;i++) p[i]=i;
	for(i=1;i<=m;i++)
		for(j=m;j>i;j--)
			if(w[p[j]]<w[p[j-1]]){
				tmp=p[j]; p[j]=p[j-1]; p[j-1]=tmp;
			}
	for(i=1;i<=m;i++) printf("%s\n",s[p[i]]);
}

int main(){
	int i,j,k;
	init();
	process();
	return 0;
}
		
