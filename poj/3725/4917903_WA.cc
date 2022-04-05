#include <iostream>
using namespace std;
int fj[15];
int tmp[10][100];
int pows[10]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
int main(){
	int k,m;
	while (scanf("%d%d",&k,&m)!=EOF){
		int len=0,mm=m;
		while (m>0){
			fj[len]=m%10;
			m/=10;
			len++;
		}
		m=mm;
		int round=0,i;
		int tmp=1,tmp2;
		while (tmp<k){
			for (i=1;i<fj[len-1];i++){
				tmp+=pows[round];
				if (tmp>=k) break;
			}
			if (tmp>=k) break;
//			cout<<"round:"<<round<<" tmp:"<<tmp<<endl;
			tmp2=0;
			i=fj[len-1];
			if (round+1<len){
				if (round==0) tmp++; 
				else {
					tmp2=m/pows[len-round-1];
					tmp2%=pows[round];
					tmp2++;
					tmp+=tmp2;
				}
			} else {
					tmp2=m%pows[len-1];
					tmp2*=pows[round-len+1];
					tmp+=tmp2;
			}
//			cout<<"round:"<<round<<" tmp:"<<tmp<<" tmp2:"<<tmp2<<endl;
			round++;
			if (round==20) break;
		}
//		cout<<fj[len-1]<<endl;
//		cout<<"len:"<<len<<endl;
//		cout<<"round:"<<round<<endl;
//		cout<<"tmp:"<<tmp<<endl;
//		cout<<"tmp2:"<<tmp2<<endl;
//		cout<<"i:"<<i<<endl;
		if (round==20) cout<<0<<endl;else{
		int ans=0;
		for (int j=1;j<=i;j++){
			ans+=pows[round];
		}
		if (i!=fj[len-1]){
			ans+=pows[round];
			ans+=k-tmp-1;
		}else {
			ans+=tmp2;
			ans+=k-tmp-1;
		}
		if (ans<m) ans=m;
		cout<<ans<<endl;	}
	}
}
