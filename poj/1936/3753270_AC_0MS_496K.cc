#include <iostream>
using namespace std;

char S[100001], T[100001];
int l1, l2;

int find(int p, int st){
	int i;
	for(i=st;i<l2;i++)
		if(T[i]==S[p]) return i;
	return -1;
}

void process(){
	int i,j,k, last;
	l1=strlen(S); l2=strlen(T);
	last=0;
	for(i=0;i<l1;i++){
		k=find(i, last);
		if(k==-1){
			cout<<"No"<<endl;
			return;
		}
		else last=k+1;
	}
	cout<<"Yes"<<endl;
}

int main(){
	int i,j,k;
//	freopen("1936.in","r",stdin);
	while(scanf("%s%s\n",S,T)!=EOF){
		process();
	}
//	while(k=1);
	return 0;
}
