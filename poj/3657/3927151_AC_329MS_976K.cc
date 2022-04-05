#include <iostream>
#include <set>
#define MaxL 100000000
using namespace std;

struct node{
	int a, b, ans;
}q[30000], A[30000];

int N, Q;
set< pair<int, int> > S;

bool cmp(node A, node B){
	return A.ans>B.ans;
}

inline int MinN(int a, int b){
	return (a<b)?a:b;
}

inline int MaxN(int a, int b){
	return (a>b)?a:b;
}

bool check(int p){
	int i,j,k, left, right, cleft, cright;
	bool flag=false;
	set< pair<int, int> >:: iterator now, pre;
	
	for(i=0; i<=p; i++) A[i]=q[i];
	sort(A, A+p+1, cmp);
	
	S.clear();
	S.insert(make_pair(-1,-1));
	S.insert(make_pair(N+10, N+10));
	
	
	for(i=0; i<=p; ++i){
		left=cleft=A[i].a;
		right=cright=A[i].b;
		
		for(j=i+1; j<=p&&A[j].ans==A[i].ans; ++j){
			left=MaxN(left, A[j].a);
			right=MinN(right, A[j].b);
			cleft=MinN(cleft, A[j].a);
			cright=MaxN(cright, A[j].b);
		}
		if(left>right) return false;
		
		now=S.upper_bound(make_pair(left, right));
		now--;
		if(now->first<=left&&right<=now->second) return false;
		
		now=pre=S.lower_bound(make_pair(cleft, cright));
		pre--;
		if(pre->second>=cleft-1){
			cleft=pre->first;
			S.erase(pre);
		}
		while(now->first<=cright+1){
			cright=MaxN(cright, now->second);
			S.erase(now++);
		}
		S.insert(make_pair(cleft, cright));
		
		i=j-1;
	}
	
	return true;
}

void process(){
	int i,j,k, ans=MaxL;
	int l=0, r=Q-1, mid;
	while(l<=r){
		mid=(l+r)/2;
		if(!check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	if(ans==MaxL) printf("0\n");
	else printf("%d\n", ans+1);
}

int main(){
	int i,j,k, ans=MaxL;
//	freopen("bales.15.in", "r", stdin);
	scanf("%d%d", &N, &Q);
	for(i=0; i<Q; i++){
		scanf("%d%d%d", &q[i].a, &q[i].b, &q[i].ans);
	}
	
	process();
	
//	while(1);
	return 0;
}