#include <iostream>
using namespace std;

int f[21][21][21];
bool cnt[21][21][21];

int w(int a, int b, int c){
	if(cnt[a][b][c])
		return f[a][b][c];
	int ans;
	if(a<=0||b<=0||c<=0) return 1;
	if(a>20||b>20|c>20) return w(20,20,20);
	if(a<b&&b<c) ans=w(a,b,c-1)+w(a,b-1,c-1)-w(a,b-1,c);
	else ans=w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1)-w(a-1,b-1,c-1);
	cnt[a][b][c]=true;
	f[a][b][c]=ans;
	return ans;
}

int main(){
	int i,j,k;
	cin>>i>>j>>k;
	while(true){
		if(i==-1&&j==-1&&k==-1) break;
		memset(cnt,0,sizeof cnt);
		printf("w(%d, %d, %d) = %d\n",i,j,k,w(i,j,k));
		cin>>i>>j>>k;
	}
	return 0;
}
