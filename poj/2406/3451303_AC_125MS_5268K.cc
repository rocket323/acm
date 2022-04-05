#include <iostream>
#define MaxL 1000001
using namespace std;

int n,p[MaxL];
char s[MaxL];

void init(){
	int i,j,k;
	n=strlen(s);
	p[0]=-1;
	j=-1;
	for(i=1;i<n;i++){
		while(j>-1&&s[j+1]!=s[i]) j=p[j];
		if(s[j+1]==s[i]) j++;
		p[i]=j;
	}
}

void process(){
	int i,j,k;
	if(p[n-1]==-1){
		printf("1\n");
		return;
	}
	if(n%(n-1-p[n-1])!=0) printf("1\n");
	else printf("%d\n",n/(n-1-p[n-1]));
}

int main(){
	int i,j,k;
	scanf("%s",s);
	while(s[0]!='.'){
		init();
		process();
		scanf("%s",s);
	}
	return 0;
}
