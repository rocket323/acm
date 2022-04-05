#include <iostream>
using namespace std;

char s1[4][100], s2[4][100], t[4][100];

bool find(char s[], char ch){
	int i=0;
	while(s[i]){
		if(s[i]==ch) return true;
		i++;
	}
	return false;
}

bool check(char ch, int tt){
	bool flag=0;
	
	for(int i=1; i<=3; ++i){
		if(find(s1[i], ch)) flag=1;
		if(find(s2[i], ch)) flag=1;
	}
	if(!flag) return false;
	
	
	if(tt==2){
		for(int i=1; i<=3; ++i){
			if( t[i][0]=='e'&&(find(s1[i], ch)||find(s2[i], ch)) ) return false;
			if( t[i][0]=='d'&&find(s1[i], ch) ) return false;
			if( t[i][0]=='u'&&find(s2[i], ch) ) return false;
		}
	}
	else{
		for(int i=1; i<=3; ++i){
			if( t[i][0]=='e'&&(find(s1[i], ch)||find(s2[i], ch))) return false;
			if( t[i][0]=='d'&&find(s2[i], ch) ) return false;
			if( t[i][0]=='u'&&find(s1[i], ch) ) return false;
		}
	}
	return true;
}

void process(){
	int i,j,k, side;
	char ch;
	
	for(i=1; i<=3; ++i)
		cin>>s1[i]>>s2[i]>>t[i];
	for(ch='A'; ch<='L'; ++ch){
		if(check(ch, 1))
			printf("%c is the counterfeit coin and it is light.\n", ch);
		if(check(ch, 2))
			printf("%c is the counterfeit coin and it is heavy.\n", ch);
	}
	
}

int main(){
//	freopen("1013t.in", "r", stdin);
//	freopen("1013.out", "w", stdout);
	int T;
	cin>>T;
	for(int i=1; i<=T; ++i){
		process();
	}
//	while(1);
	return 0;
}
