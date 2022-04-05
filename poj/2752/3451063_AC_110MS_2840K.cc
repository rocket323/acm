#include <iostream>
#define MaxL 400001
using namespace std;

char s[MaxL];
int n;
int p[MaxL],ans[MaxL],tp;

void KMP(){
	int i,j,k;
	n=strlen(s);
	p[0]=-1;
	j=-1;
	for(i=1;i<n;i++){
		while(j>-1&&s[j+1]!=s[i]) j=p[j];
		if(s[j+1]==s[i]) j++;
		p[i]=j;
	}
	k=n-1; tp=1; ans[1]=n;
	while(p[k]!=-1){
		tp++;
		ans[tp]=p[k]+1;
		k=p[k];
	}
}

void out(){
	for(int i=tp;i>1;i--) printf("%d ",ans[i]);
	printf("%d\n",ans[1]);
}	

int main(){
	int i,j,k;
//	freopen("2752.in","r",stdin);
	while(scanf("%s",s)!=EOF){
		KMP();
		out();
	}
//	while(k=1);
	return 0;
}
