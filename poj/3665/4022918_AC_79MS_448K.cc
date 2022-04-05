#include <iostream>
using namespace std;

int N, r[1001];

int main(){
	int i,j,k,t, Max, rec, tmp;
//	freopen("1042.in","r",stdin);
	cin>>N>>t;
	for(i=1;i<=N;i++) cin>>r[i];
	for(i=1;i<=t;i++){
		Max=-1;
		for(j=1;j<=N;j++)
			if(Max<r[j]){
				Max=r[j];
				rec=j;
			}
		tmp=r[rec]%(N-1);
		
		cout<<rec<<endl;
		for(j=1;j<=N;j++)
			if(j!=rec)
				r[j]+=(r[rec]/(N-1));
		r[rec]=0;
		for(j=1;j<=N;j++){
			if(tmp==0) break;
			if(j==rec) continue;
			r[j]++; tmp--;
		}
	}
//	while(k=1);
	return 0;
}