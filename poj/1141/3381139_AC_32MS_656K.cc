#include <iostream>
using namespace std;
#define MaxL 10000000

int len=0,n,i,j,k;
int f[201][201]={0},nexti[201][201]={0},nextj[201][201]={0},root[101][101]={0};
char s[1001];

void init(){
	char ch;
	int i,j,k;
	while(cin>>ch){
		len++;
		s[len]=ch;
	}
	for(i=1;i<=len;i++)
		for(j=1;j<=len;j++)
			if(i==j) f[i][j]=1;
			else if(i<j) f[i][j]=MaxL;
}

bool match(char ch1, char ch2){
	if(ch1=='['&&ch2==']') return true;
	if(ch1=='('&&ch2==')') return true;
	return false;
}

void DP(){
	int i,j,k,t,x;
	for(k=2;k<=len;k++)
		for(i=1;i<=len-k+1;i++){
			j=i+k-1;
			for(x=i;x<j;x++)
				if(f[i][x]+f[x+1][j]<f[i][j]){
					f[i][j]=f[i][x]+f[x+1][j];
					root[i][j]=x;
				}
			if(match(s[i],s[j])) t=0; else t=2;
			if(f[i+1][j-1]+t<f[i][j]){
				nexti[i][j]=i+1;
				nextj[i][j]=j-1;
				root[i][j]=0;
				f[i][j]=f[i+1][j-1]+t;
			}
		}
}

void makeup(char c){
	if(c=='(') printf("()");
	if(c==')') printf("()");
	if(c=='[') printf("[]");
	if(c==']') printf("[]");
}

void out(int l, int r){
	if(l>r) return;
	if(l==r) {makeup(s[r]); return;}
	int k=root[l][r];
	if(k==0){
		if(match(s[l],s[r])){
			printf("%c",s[l]);
			out(l+1,r-1);
			printf("%c",s[r]);
		}
		else{
			makeup(s[l]);
			out(l+1,r-1);
			makeup(s[r]);
			out(l+1,r-1);
		}
		return;
	}
	out(l,k);
	out(k+1,r);
}

int main(){
	init();
	DP();
	out(1,len);
	printf("\n");
	return 0;
}
