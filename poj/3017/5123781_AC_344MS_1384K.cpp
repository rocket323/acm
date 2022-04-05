// 
// File:   3017.cc
// Author: Administrator
// 动态规划，加优化。
// Created on 2007年12月29日, 下午2:09
//

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long llong;
const int MAXN=100010;

int N;
llong M;
int arr[MAXN];
llong ans[MAXN];
int key[MAXN];

void input(){
    for (int i=1;i<=N;i++)
	scanf("%d",&arr[i]);
}

void solve(){
    int i,j;
    for (i=1;i<=N;i++)
	if (arr[i]>M){
	    printf("-1\n");
	    return;
	}

    llong curSum=0;
    ans[0]=0;
    int idx_start=1;
    int key_idx_st=0,key_idx_end=1;
    key[0]=1;
    for (i=1;i<=N;i++){
	curSum += arr[i];
	while (curSum>M){
	    curSum-=arr[idx_start];
	    idx_start++;
	}
	
	while (key_idx_st<key_idx_end && key[key_idx_st]<idx_start)
	    key_idx_st++;
	
	while (key_idx_end>key_idx_st && arr[key[key_idx_end-1]]<=arr[i])
	    key_idx_end--;
	key[key_idx_end]=i;
	key_idx_end++;
	
	ans[i]=ans[idx_start-1]+arr[key[key_idx_st]];
	for (j=key_idx_st;j<key_idx_end-1;j++)
	    ans[i]=min(ans[i],ans[key[j]]+arr[key[j+1]]);
    }
    
    printf("%I64d\n",ans[N]);
}

int main(int argc, char** argv) {
    while (scanf("%d%I64d",&N,&M)!=EOF){
	input();
	solve();
    }
    return (EXIT_SUCCESS);
}