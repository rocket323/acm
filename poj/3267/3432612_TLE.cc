#include <iostream>
#define MaxL 100000000
using namespace std;

char word[601][26];
char str[301];
int l,n,m,w;
int f[301];

void init(){
	int i,j,k;
	scanf("%d%d",&w,&n);
	scanf("%s",str);
	for(i=1;i<=w;i++)
		scanf("%s",word[i]);
	memset(f,0,sizeof f);
}

void tryword(int k, int start, int end){
	int i,j,s,t,p,q;
	s=start; t=end; i=0;
	for(j=1;j<=strlen(word[k]);j++){
		while(str[s]!=word[k][i]&&s<=end) s++;
		if(s>end) return;
		s++; i++;
	}
	int num=end-start+1-strlen(word[k]);
	if(f[end]>f[start-1]+num)
		f[end]=f[start-1]+num;
}

void process(){
	int i,j,k;
	for(i=1;i<=n;i++)
		f[i]=MaxL;
	f[0]=0;
	char st[301]=" ";
	strcat(st,str);
	
	strcpy(str,st);

	for(i=1;i<=n;i++)
		for(j=0;j<i;j++)
			for(k=1;k<=w;k++)
				if(word[k][0]==str[j+1])
					tryword(k,j+1,i);
	printf("%d\n",f[n]);
}

int main(){
	int i,j,k;
	init();
	process();
	return 0;
}
