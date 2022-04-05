#include <iostream>
#define MaxL 10000000
using namespace std;

char S[21][21];
int f[1<<20][21], d[21][21], N;

void make(int a, int b){
	int i,j,k, l1, l2, s1, s2;
	l1=strlen(S[a]); l2=strlen(S[b]);
	for(i=0;i<l1;i++){
		if(l1-i>l2) continue;
		s1=i; s2=0;
		while(s1<l1){
			if(S[a][s1]!=S[b][s2]) break;
			s1++; s2++;
		}
		if(s1==l1){
			d[a][b]=l2-l1+i;
			return;
		}
	}
	d[a][b]=l2;
}

void init(){
	int i,j,k;
	for(i=1;i<=N;i++)
		scanf("%s",S[i]);
	for(i=1;i<=N;i++)
		for(j=1;j<=N;j++)
			if(i==j) d[i][j]=0;
			else make(i, j);
}

int Min(int a, int b){
	return(a<b)?a:b;
}

void process(){
	int i,j,k, tmp, t2, tot=(1<<N)-1;
	int ans=MaxL;
	
	for(i=0; i<=tot; i++)
		for(j=0; j<=N; j++)
			f[i][j]=MaxL;
	
	for(i=1;i<=N;i++) f[1<<(i-1)][i]=strlen(S[i]);
	
	for(i=0; i<(1<<N); i++)
		for(j=1; j<=N; j++){
			if(f[i][j]==MaxL) continue;
			tmp=1<<(j-1);
			if(i&tmp==0) continue;
			for(k=1; k<=N; k++){
				t2=1<<(k-1);
				if(i&t2) continue;
				f[i|t2][k]=Min(f[i|t2][k], f[i][j]+d[j][k]);
			}
		}
	for(i=1; i<=N; i++)
		if(f[tot][i]<ans) ans=f[tot][i];
	cout<<ans<<endl;
//	printf("Elenore can use a string of length %d.\n",ans);
}

int main(){
	int i,j,k,T;
//	freopen("E.in","r",stdin);
	while(scanf("%d", &N)!=EOF){
		init();
		process();
	}
//	while(k=1);
	return 0;
}

