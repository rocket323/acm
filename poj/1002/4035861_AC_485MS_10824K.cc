#include <iostream>
#include <algorithm>
using namespace std;

char S[100001][100];
int N, ans[100001], cnt[100010];
int st[100001], top;

void init(){
	int i,j,k;
	scanf("%d", &N);
	for(i=1; i<=N; ++i) scanf("%s", S[i]);
}

void out(){
	int i,j,k, tt=0, tmp;
	char s[10]="";
	for(i=1; i<8; ++i) strcat(s, " ");
	for(i=1; i<=top; ++i){
		if(cnt[i]==1) continue;
		k=st[i];
		tt=0;
		while(k>0){
			tmp=k%10;
			s[tt++]=(char)(tmp+'0');
			k/=10;
		}
		if(tt<7){
			for(j=tt; j<7; ++j) s[j]='0';
		}
		for(j=6; j>=4; --j) cout<<s[j];
		cout<<'-';
		for(j=3; j>=0; --j) cout<<s[j];
		cout<<' '<<cnt[i]<<endl;
	}
}

int getID(char ch){
	if('A'<=ch&&ch<='C') return 2;
	if('D'<=ch&&ch<='F') return 3;
	if('G'<=ch&&ch<='I') return 4;
	if('J'<=ch&&ch<='L') return 5;
	if('M'<=ch&&ch<='O') return 6;
	if('P'<=ch&&ch<='S') return 7;
	if('T'<=ch&&ch<='V') return 8;
	if('W'<=ch&&ch<='Y') return 9;
}
int form(int now){
	int i=0,j,k, ans=0;
	while(S[now][i]){
		if('0'<=S[now][i]&&S[now][i]<='9')
			ans=ans*10+(S[now][i]-'0');
		else if('A'<=S[now][i]&&S[now][i]<='Z')
			ans=ans*10+getID(S[now][i]);
		i++;
	}
	return ans;
}

void process(){
	int i,j,k;
	for(i=1; i<=N; ++i)
		ans[i]=form(i);
	sort(ans+1, ans+1+N);
	st[1]=ans[1]; cnt[1]=1; top=1;
	for(i=2; i<=N; ++i){
		if(ans[i]==st[top])
			cnt[top]++;
		else{
			if(cnt[top]>1) top++;
			st[top]=ans[i];
			cnt[top]=1;
		}
	}
//	for(i=1; i<=N; ++i) cout<<ans[i]<<endl;
	if(top==1&&cnt[top]==1) printf("No duplicates.\n");
	else out();
}

int main(){
//	freopen("1002.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
