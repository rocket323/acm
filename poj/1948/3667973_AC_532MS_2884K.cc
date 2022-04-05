#include <iostream>
#include <cmath>
using namespace std;

int N, A[41];
bool f[1601][1601];
int sum;
double ans, tmp;

void init(){
	int i,j,k;
	scanf("%d",&N);
	sum=0;
	for(i=1;i<=N;i++){
		scanf("%d",&A[i]);
		sum+=A[i];
	}
}

bool check(int a, int b, int c){
	if(a<=0||b<=0||c<=0) return false;
	if(a+b<=c) return false;
	if(a+c<=b) return false;
	if(b+c<=a) return false;
	return true;
}

double area(int a, int b, int c){
	double t=(a+b+c)/2.0;
	double ans=sqrt(t*(t-a)*(t-b)*(t-c));
	return ans;
}

void process(){
	int i,j,k, l1, l2, l3;
	memset(f, 0, sizeof f);
	f[0][0]=1;
	for(i=1;i<=N;i++)
		for(j=sum;j>=0;j--)
			for(k=sum;k>=0;k--){
				if(j-A[i]>=0&&f[j-A[i]][k]) f[j][k]=1;
				if(k-A[i]>=0&&f[j][k-A[i]]) f[j][k]=1;
			}
	ans=0;
	for(i=0;i<=sum;i++)
		for(j=0;j<=sum;j++){
			k=sum-i-j;
			if(!check(i,j,k)) continue;
			if(!f[i][j]) continue;
		//	cout<<i<<' '<<j<<' '<<k<<endl;
			tmp=area(i, j, k);
			if(tmp>ans) ans=tmp;
		}
	k=ans*100;
	if(k!=0)
		printf("%d\n",k);
	else printf("-1\n");
}

int main(){
	int i,j,k;
//	freopen("pasturc.9.in","r",stdin);
//	freopen("1948.out","w",stdout);
	init();
	process();
//	while(k=1);
	return 0;
}
