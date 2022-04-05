#include <iostream>
using namespace std;

char s[1001][22];
int n;

void process(){
	int i,j,k,l1,l2;
	char s1[22], s2[22];
	bool flag;
	for(i=1;i<=n;i++){
		l1=strlen(s[i]);
		for(j=l1;j>=1;j--){
			strncpy(s1,s[i],j);
			s1[j]='\0';
			flag=false;
			for(k=1;k<=n;k++)
				if(k!=i){
					l2=strlen(s[k]);
					if(l2>=j){
						strncpy(s2,s[k],j);
						s2[j]='\0';
						if(strcmp(s1,s2)==0){
							flag=true;
							break;
						}
					}
				}
			if(flag){
				printf("%s ",s[i]);
				if(j<l1)
					for(k=0;k<=j;k++) printf("%c",s[i][k]);
				else
					for(k=0;k<j;k++) printf("%c",s[i][k]);
				printf("\n");
				break;
			}
		}
	}
}

int main(){
	int i,j,k;
//	freopen("2001.in","r",stdin);
	n=1;
	while(scanf("%s",s[n])!=EOF){
		n++;
	}
	n--;
	process();
//	while(k=1);
	return 0;
}
