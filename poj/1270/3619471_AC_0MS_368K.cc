#include <iostream>
#include <string>
#define MaxL 100000
using namespace std;

int d[27],N, nex[27], G[27][27];
char s1[102], s2[102], s[102];
char A[102];

int getID(char c){
	int i;
	for(i=1;i<=N;i++)
		if(s[i]==c)
			return i;
}

void init(){
	int i,j,k,a,b;
	char tmp;
	i=0; N=0;
	memset(d,0,sizeof d);
	memset(nex,0,sizeof nex);
	while(i<strlen(s1)){
		N++;
		s[N]=s1[i];
		i+=2;
	}
	for(i=1;i<N;i++)
		for(j=i+1;j<=N;j++)
			if(s[i]>s[j]){
				tmp=s[i]; s[i]=s[j]; s[j]=tmp;
			}
	i=0;
	while(i<strlen(s2)){
		a=getID(s2[i]);
		b=getID(s2[i+2]);
		i+=4;
		d[b]++;
		nex[a]++;
		G[a][nex[a]]=b;
	}
}

void out(){
	int i;
	for(i=1;i<=N;i++)
		printf("%c",A[i]);
	printf("\n");
}

void sort(int now){
	int i,j,k,save;
	for(i=1;i<=N;i++)
		if(d[i]==0){
			A[now]=s[i];
			if(now==N) out();
			else{
				save=d[i]; d[i]=MaxL;
				for(j=1;j<=nex[i];j++)
					d[G[i][j]]--;
				sort(now+1);
				for(j=1;j<=nex[i];j++)
					d[G[i][j]]++;
				d[i]=save;
			}
		}
}

int main(){
	int i,j,k;
//	freopen("1270.in","r",stdin);
	while(gets(s1)){
		gets(s2);
		init();
		sort(1);
		printf("\n");
	}
//	while(k=1);
	return 0;
}
