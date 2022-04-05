#include <iostream>
using namespace std;

int N;
char S[10001][11];

void qsort(int s, int t){
	int i=s, j=t;
	char x[11], tmp[11];
	strcpy(x, S[(s+t)/2]);
	while(i<j){
		while(strcmp(S[i], x)<0) i++;
		while(strcmp(S[j], x)>0) j--;
		if(i<=j){
			strcpy(tmp, S[i]); strcpy(S[i], S[j]); strcpy(S[j], tmp);
			i++; j--;
		}
	}
	if(i<t) qsort(i, t);
	if(s<j) qsort(s, j);
}

void init(){
	int i,j,k;
	scanf("%d",&N);
	for(i=1;i<=N;i++)
		scanf("%s",&S[i]);
	qsort(1, N);
}

bool check(int i, int j){
	int k, l1, l2;
	for(k=0;S[i][k]&&S[j][k];k++){
		if(S[i][k]!=S[j][k])
			return false;
	}
	return true;
}

void process(){
	int i,j,k;
	for(i=1;i<N;i++)
		if(check(i,i+1)){
			cout<<"NO\n";
			return;
		}
	cout<<"YES\n";
}	

int main(){
	int i,j,k,T;
//	freopen("3630.in","r",stdin);
	scanf("%d",&T);
	for(i=1;i<=T;i++){
		init();
		process();
	}
//	while(k=1);
	return 0;
}
