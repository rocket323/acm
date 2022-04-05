#include <iostream>
#define MaxL 1000001
using namespace std;

int n,p[MaxL];
char s[MaxL];

void init(){
	int i,j,k;
	scanf("%s",s);
	p[0]=-1;
	j=-1;
	for(i=1;i<n;i++){
		while(j>-1&&s[j+1]!=s[i]) j=p[j];
		if(s[j+1]==s[i]) j++;
		p[i]=j;
	}
}

void process(int step){
	int i,j,k;
	printf("Test case #%d\n",step);
	for(i=1;i<n;i++)
		if(p[i]>-1)
			if((i+1)%(i-p[i])==0){
				printf("%d %d\n",i+1,(i+1)/(i-p[i]));
			}
	printf("\n");
}

int main(){
	int i,j,k;
	scanf("%d",&n);
	k=0;
	while(n!=0){
		k++;
		init();
		process(k);
		scanf("%d",&n);
	}
	return 0;
}
