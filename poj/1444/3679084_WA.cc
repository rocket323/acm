#include <iostream>
#define MaxL 100000000
#include <cmath>
using namespace std;

int x1,yy1,z1,x2,y2,z2,L,W,H,d1,d2;
int tx1,tyy1, tx2, ty2;
int ans;

void init(){
	int i,j,k;
	cin>>L>>W>>H;
	cin>>x1>>yy1>>z1;
	cin>>x2>>y2>>z2;
}

int Min(int a, int b, int c, int d){
	int ans=MaxL;
	if(ans>a) ans=a;
	if(ans>b) ans=b;
	if(ans>c) ans=c;
	if(ans>d) ans=d;
	return ans;
}

void process(){
	int i,j,k;
	double ans;
	
	
	if(x1==0){
		if(x2==0){
			d1=yy1-y2;
			d2=z1-z2;
		}
		else if(x2==L){
			d1=yy1-y2;
			d2=Min(z1+z2+L, H-z1+L+H-z2, z1+z2+L, H-z1+H-z2+L);
		}
		else if(y2==0){
			d1=z1-z2;
			d2=yy1+x2;
		}
		else if(y2==W){
			d1=z1-z2;
			d2=W-yy1+x2;
		}
		else if(z2==0){
			d1=yy1-y2;
			d2=z1+x2;
		}
		else if(z2==H){
			d1=yy1-y2;
			d2=H-z1+x2;
		}
	}
	else if(x1==L){
		if(x2==L){
			d1=yy1-y2;
			d2=z1-z2;
		}
		else if(x2==0){
			d1=yy1-y2;
			d2=Min(z1+z2+L, H-z1+L+H-z2, z1+z2+L, H-z1+H-z2+L);
		}
		else if(y2==0){
			d1=z1-z2;
			d2=yy1+L-x2;
		}
		else if(y2==W){
			d1=z1-z2;
			d2=W-yy1+L-x2;
		}
		else if(z2==0){
			d1=yy1-y2;
			d2=z1+L-x2;
		}
		else if(z2==H){
			d1=yy1-y2;
			d2=H-z1+L-x2;
		}
	}
	else if(yy1==0){
		if(y2==0){
			d1=x1-x2;
			d2=z1-z2;
		}
		else if(y2==W){
			d1=x1-x2;
			d2=Min(z1+W+z2, H-z1+H-z2+W, x1+x2+W, L-x1+L-x2+W);
		}
		else if(x2==0){
			d1=z1-z2;
			d2=x1+y2;
		}
		else if(x2==L){
			d1=z1-z2;
			d2=L-x1+y2;
		}
		else if(z2==0){
			d1=x1-x2;
			d2=z1+y2;
		}
		else if(z2==H){
			d1=x1-x2;
			d2=H-z1+y2;
		}
	}
	else if(yy1==W){
		if(y2==W){
			d1=x1-x2;
			d2=z1-z2;
		}
		else if(y2==0){
			d1=x1-x2;
			d2=Min(z1+W+z2, H-z1+H-z2+W, x1+x2+W, L-x1+L-x2+W);
		}
		else if(x2==0){
			d1=z1-z2;
			d2=x1+W-y2;
		}
		else if(x2==L){
			d1=z1-z2;
			d2=L-x1+W-y2;
		}
		else if(z2==0){
			d1=x1-x2;
			d2=z1+W-y2;
		}
		else if(z2==H){
			d1=x1-x2;
			d2=H-z1+W-y2;
		}
	}
	else if(z1==0){
		if(z2==0){
			d1=x1-x2;
			d2=yy1-y2;
		}
		else if(z2==H){
			d1=x1-x2;
			d2=Min(yy1+H+y2, W-yy1+H+W-y2, x1+x2+H, L-x1+L-x2+H);
		}
		else if(x2==0){
			d1=yy1-y2;
			d2=x1+z2;
		}
		else if(x2==L){
			d1=yy1-y2;
			d2=L-x1+z2;
		}
		else if(y2==0){
			d1=x1-x2;
			d2=yy1+z2;
		}
		else if(y2==W){
			d1=x1-x2;
			d2=W-yy1+z2;
		}
		
	}
	else if(z1==H){
		if(z2==H){
			d1=x1-x2;
			d2=yy1-y2;
		}
		else if(z2==0){
			d1=x1-x2;
			d2=Min(yy1+H+y2, W-yy1+H+W-y2, x1+x2+H, L-x1+L-x2+H);
		}
		else if(x2==0){
			d1=yy1-y2;
			d2=x1+H-z2;
		}
		else if(x2==L){
			d1=yy1-y2;
			d2=L-x1+H-z2;
		}
		else if(y2==0){
			d1=x1-x2;
			d2=yy1+H-z2;
		}
		else if(y2==W){
			d1=x1-x2;
			d2=W-yy1+H-z2;
		}
		
	}
	
	
	ans=d1*d1+d2*d2;
//	cout<<tx1<<' '<<tyyy1<<' '<<tx2<<' '<<ty2<<endl;
	printf("%d\n",ans);
}

int main(){
	int i,j,k,T;
//	freopen("D.in","r",stdin);
	cin>>T;
	for(i=1;i<=T;i++){
		init();
		process();
	}
//	while(k=1);
	return 0;
}
