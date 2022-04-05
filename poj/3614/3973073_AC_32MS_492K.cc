#include <iostream>
#include <algorithm>
using namespace std;

struct Cow{
	int a, b;
}CC[3000];

struct Lotion{
	int p, cov;
}LL[3000];

int C, L;
bool vis[3000];

bool cmp(Cow A, Cow B){
	return (A.b<B.b||(A.b==B.b&&A.a<B.a));
}

bool cmp2(Lotion A, Lotion B){
	return (A.p<B.p);
}

void init(){
	int i,j,k;
	scanf("%d%d", &C, &L);
	for(i=0; i<C; i++) scanf("%d%d", &CC[i].a, &CC[i].b);
	for(i=0; i<L; i++) scanf("%d%d", &LL[i].p, &LL[i].cov);
	sort(CC, CC+C, cmp);
	sort(LL, LL+L, cmp2);
}

int process(){
	int i,j,k, ans=0, cnt;
	memset(vis, 0, sizeof vis);
	
	for(i=0; i<C; i++){
		for(j=0; j<L; j++){
			if(CC[i].a<=LL[j].p&&LL[j].p<=CC[i].b&&LL[j].cov>0){
				LL[j].cov--;
				ans++;
				break;
			}
		}
	}
	
	return ans;
}

int main(){
//	freopen("3614.in", "r", stdin);
	init();
	cout<<process()<<endl;
//	while(1);
	return 0;
}
