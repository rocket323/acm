#include <iostream>
#include <cmath>
using namespace std;

int N, A[33];
bool ans[33], stop[33], arr[33], Find;

void init(){
	int i,j,k;
	for(i=1;i<=N;i++)
		scanf("%d",&A[i]);
}

void dfs(int floor, int Time, int reach, int Lim){

	if(Find) return;
//	if(floor>=32&&reach<N) return;
	if(floor>=32) return;
	if(reach==N){
		Find=true;
		memcpy(ans, stop, sizeof stop);
		return;
	}
	
	int i,j,k;
	bool can=true;
	for(i=1;i<=N;i++)
		if(!arr[i]&&A[i]<=floor+1)
			if(Time+4+20*abs(floor+1-A[i])>Lim){
				can=false;
				break;
			}
	if(can)
		dfs(floor+1, Time+4, reach, Lim);
	else{
		stop[floor]=1;
		int cnt=0, save[33];
		memcpy(save, arr, sizeof arr);
		for(i=1;i<=N;i++)
			if((Time+abs(floor-A[i])*20<=Lim)&&!arr[i]){
				cnt++;
				arr[i]=1;
			}
		dfs(floor+1, Time+14, reach+cnt, Lim);
		
	}
}

bool check(int T){
	int i,j,k;
	memset(stop, 0, sizeof stop);
	memset(arr, 0, sizeof arr);
	Find=false;
	dfs(2, 4, 0, T);
	return Find;
}

void out( ){
	int i,j,k=0;
	for(i=1;i<=31;i++)
		if(ans[i]) k++;
	cout<<k<<' ';
	for(i=1;i<=31;i++)
		if(ans[i]){
			k--;
			if(k) cout<<i<<' ';
			else cout<<i<<endl;
		}
}

void process(){
	int i,j,k, l, r, mid;
	l=0; r=600;
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)) r=mid-1;
		else l=mid+1;
	}
	cout<<mid<<endl;
	out( );
}

int main(){
	int i,j,k;
//	freopen("1771.in","r",stdin);
//	freopen("1771.out","w",stdout);
	scanf("%d",&N);
	while(N!=0){
		init();
		process();
		scanf("%d",&N);
	}
//	while(k=1);
	return 0;
}
