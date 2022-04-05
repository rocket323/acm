#include <iostream>
using namespace std;

int n,a[101],f[101][45200]={0};

int main(){
	int i,j,k,sum=0,mid,l1,l2,l;
	//freopen("2576.in","r",stdin);
	cin>>n;
	mid=n/2;
	for(i=1;i<=n;i++){ cin>>a[i]; sum+=a[i]; }
	f[0][0]=1;
	for(i=1;i<=n;i++)
		for(j=a[i];j<=sum;j++)
			if(f[i-1][j-a[i]]){
				f[i][j]=1;
				f[i][j-a[i]]=1;
			}
	k=sum/2; l1=0; l2=0;
	if(n%2==1){
		for(i=k;i>=0;i--)
			if(f[mid][i]){
				l1=i;
				break;
			}
		for(i=k;i>=0;i--)
			if(f[mid+1][i]){
				l2=i;
				break;
			}
		l=(l1>l2)?l1:l2;
		cout<<l<<' '<<sum-l<<endl;
	}
	else{
		for(i=k;i>=0;i--)
			if(f[mid][i]){
				l=i;
				break;
			}
		cout<<l<<' '<<sum-l<<endl;
	}
//	while(k=1);
	return 0;
}
