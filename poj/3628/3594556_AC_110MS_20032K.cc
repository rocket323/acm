#include<iostream>
using namespace std;

int N,B,h[21],s=0;
bool can[20000001];

int main(){
	int i,j,k;
//	freopen("3628.in","r",stdin);
	cin>>N>>B;
	for(i=1;i<=N;i++){
		cin>>h[i];
		s+=h[i];
	}
	memset(can,0,sizeof can);
	can[0]=true;
	for(i=1;i<=N;i++)
		for(j=s;j>=h[i];j--)
			if(can[j-h[i]])
				can[j]=true;
	for(i=B;i<=s;i++)
		if(can[i])
			break;
	cout<<(i-B)<<endl;
//	while(k=1);
	return 0;
}
