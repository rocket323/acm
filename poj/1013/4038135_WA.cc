#include <iostream>
using namespace std;

int Lv[100];

void process(){
	int i,j,k, side;
	char ch;
	char s1[4][100], s2[4][100], t[4][100];
	memset(Lv, 0, sizeof Lv);
	for(i=1; i<=3; ++i){
		cin>>s1[i]>>s2[i]>>t[i];
		if(t[i][0]=='e'){
			for(j=0; j<strlen(s1[i]); ++j){
				Lv[(int)s1[i][j]]=1;
				Lv[(int)s2[i][j]]=1;
			}
		}
	}
	for(i=1; i<=3; ++i){
		if(t[i][0]!='e'){
			k=i;
			for(j=0; j<strlen(s1[i]); ++j){
				if(Lv[(int)s1[i][j]]!=1){ ch=s1[i][j]; side=1; }
				if(Lv[(int)s2[i][j]]!=1){ ch=s2[i][j]; side=2; }
			}
		}
	}
	if((t[k][0]=='u'&&side==1)||(t[k][0]=='d'&&side==2))
		printf("%c is the counterfeit coin and it is heavy.\n", ch);
	else 
		printf("%c is the counterfeit coin and it is light.\n", ch);
}

int main(){
//	freopen("1013.in", "r", stdin);
	int T;
	cin>>T;
	for(int i=1; i<=T; ++i){
		process();
	}
//	while(1);
	return 0;
}
