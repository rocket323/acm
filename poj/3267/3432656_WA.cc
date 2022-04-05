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

void tryword(int k, int end){
	int i,j,s,t,p,q;
	t=end; i=strlen(word[k])-1;
	for(j=1;j<=strlen(word[k]);j++){
		while(str[t]!=word[k][i]&&t>=0) t--;
		if(t<0) return;
		t--; i--;
	}
	t++;
	int num=end-t+1-strlen(word[k]);
	if(f[end]>f[t-1]+num)
		f[end]=f[t-1]+num;
}

void process(){
	int i,j,k,len;
	for(i=1;i<=n;i++)
		f[i]=MaxL;
	f[0]=0;
	char st[301]=" ";
	strcat(st,str);
	
	strcpy(str,st);

	for(i=1;i<=n;i++){
		for(k=1;k<=w;k++){
			len=strlen(word[k]);
			if(word[k][len-1]==str[i])
				tryword(k,i);
		}
		if(f[i]+1<f[i+1]) f[i+1]=f[i]+1;
	}
	printf("%d\n",f[n]);
}

int main(){
	int i,j,k;
	init();
	process();
	return 0;
}
