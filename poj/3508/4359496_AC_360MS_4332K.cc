#include <iostream>
#define MM 1000010
using namespace std;

int top;
char ans[MM];
char N[MM], save[MM], NN[MM];

void output(){
	for(int i=top; i>1; --i) printf("%c", ans[i]);
	printf("%c\n", ans[1]);	
}

void process(long long tes){
	int i,j,k, last=0;
	top = 0;
	strcpy(save, NN);
	printf("%I64d. ", tes);
	strcpy(N, "1"); strcat(N, NN);
	int pos = strlen(N)-1;
	while(pos){
		char p = N[pos]-last;
		if(p<'0'){ p += 10; N[pos-1] -= 1; }
		ans[++top] = p;
		pos--;
		last = p-'0';
	}
	while(ans[top]=='0') top--;
	if(strlen(save)!=top) cout<<"IMPOSSIBLE"<<endl;
	else output();
}

int main(){
	long long k = 0;
	while(gets(NN)){
		if(NN[0]=='0') break;
		process(++k);
	}
	return 0;
}
