#include <iostream>
using namespace std;

int process(char s[]){
	int i,sum=0;
	char c;
	for(i=0;s[i]!='\0';i++){
		if(s[i]!=' ')
			sum+=(s[i]-'A'+1)*(i+1);
	}
	return sum;
}

int main(){
	int i,j,k;
	char s[500];
	gets(s);
	while(s[0]!='#'){
		printf("%d\n",process(s));
		gets(s);
	}
	return 0;
}
