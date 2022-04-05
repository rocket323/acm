#include <iostream>
#define MaxL 10000000
using namespace std;

int N1, N2;
char S1[200], S2[200];
int f[200][200];

void init(){
	int i,j,k;
	cin>>N1>>S1;
	cin>>N2>>S2;
}

int getScore(char a, char b){
	char tmp;
	if(a>b){
		tmp=a; a=b; b=tmp;
	}
	if(a==' '){
		if(b=='A') return -3;
		if(b=='C') return -4;
		if(b=='G') return -2;
		if(b=='T') return -1;
		if(b==' ') return -MaxL;
	}
	if(a=='A'){
		if(b=='A') return 5;
		if(b=='C') return -1;
		if(b=='G') return -2;
		if(b=='T') return -1;
	}
	if(a=='C'){
		if(b=='C') return 5;
		if(b=='G') return -3;
		if(b=='T') return -2;
	}
	if(a=='G'){
		if(b=='G') return 5;
		if(b=='T') return -2;
	}
	if(a=='T'){
		if(b=='T') return 5;
	}
}

void process(){
	int i,j,k;
	char ch=' ';
	for(i=0; i<=N1; i++)
		for(j=0; j<=N2; j++)
			f[i][j]=-MaxL;
	f[0][0]=0;
	for(i=1; i<=N1; i++)
		f[i][0]=f[i-1][0]+getScore(S1[i-1], ch);
	for(i=1; i<=N2; i++)
		f[0][i]=f[0][i-1]+getScore(S2[i-1], ch);
	
	for(i=1; i<=N1; i++)
		for(j=1; j<=N2; j++){
			if(f[i-1][j-1] + getScore(S1[i-1], S2[j-1]) > f[i][j])
				f[i][j] = f[i-1][j-1] + getScore(S1[i-1], S2[j-1]);
			if(f[i][j-1] + getScore(S2[j-1], ch) > f[i][j])
				f[i][j] = f[i][j-1] + getScore(S2[j-1], ch);
			if(f[i-1][j] + getScore(S1[i-1], ch) > f[i][j])
				f[i][j] = f[i-1][j] + getScore(S1[i-1], ch);
		}
		
	cout<<f[N1][N2]<<endl;
}	

int main(){
	int i,j,k, T;
//	freopen("1080.in","r",stdin);
	scanf("%d", &T);
	for(i=1;i<=T; i++){
		init();
		process();
	}
//	while(k=1);
	return 0;
}
