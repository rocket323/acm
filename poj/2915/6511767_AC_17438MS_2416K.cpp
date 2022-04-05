/*
   wefowfhwefiowfw
   wefowfhwefiowfw
   wefowfhwefiowfw
   wefowfhwefiowfw
   wefowfhwefiowfw
   wefowfhwefiowfw
   wefowfhwefiowfw
   wefowfhwefiowfw
   wefowfhwefiowfw
   wefowfhwefiowfw
   wefowfhwefiowfw
   wefowfhwefiowfw
   fwefegioerghegoifsffwoifhegioeu
   fwefegioerghegoifsffwoifhegioeu
   fwefegioerghegoifsffwoifhegioeu
   fwefegioerghegoifsffwoifhegioeu
   fwefegioerghegoifsffwoifhegioeu
   fwefegioerghegoifsffwoifhegioeu
   fwefegioerghegoifsffwoifhegioeu
   fwefegioerghegoifsffwoifhegioeu
   fwefegioerghegoifsffwoifhegioeu
   fwefegioerghegoifsffwoifhegioeu
   fwefegioerghegoifsffwoifhegioeu
   fwefegioerghegoifsffwoifhegioeu
*/
#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;

struct Seg {
	unsigned char len, next;
}seg[200];
char clr[256];
unsigned top[256];

int m, p;
void read() {
	char str[256];
	
	gets(str);
	p=0;
	for(int i=0;str[i];) {
		char c=str[i];
		int j;
		for(j=i;str[j]==c;j++);
		clr[p]=c-'A';
		seg[p++].len=min(j-i, m-1);
		i=j;
	}

	unsigned char nxt[26];
	memset(nxt, -1, sizeof(nxt));
	for(int i=p-1;i>=0;i--) {
		seg[i].next=nxt[clr[i]];
		nxt[clr[i]]=i;
	}
	memset(nxt, 0, sizeof(nxt));
	for(int i=0;i<p;i++) {
		int t=nxt[clr[i]]+seg[i].len;
		if(nxt[clr[i]]<m&&t>=m) t=m-1+seg[i].len;
		else if(t>=m*2-1) t=m*2-2;
		nxt[clr[i]]=t;
		top[i]=nxt[clr[i]];
	}
}

short dp[201][200][40];
int inline chg(int l, int pre) {
	int t=l+pre;
	if(pre<m && t>=m) return m-1+l;
	else if(t<m*2-1) return t;
	else return l;
}
int main() {
	while(scanf("%d\n", &m)!=EOF) {
		read();
		for(int l=p-1;l>=0;l--) {
			int tt=top[l];
			for(int r=l;r<p;r++) {
				for(int pre=seg[l].len;pre<=tt;pre++) {
					int res=max(0, m-pre)+dp[l+1][r][seg[l+1].len];
					for(int nr=seg[l].next;nr<=r;nr=seg[nr].next)
						res=min(res, dp[nr][r][chg(seg[nr].len, pre)]+dp[l+1][nr-1][seg[l+1].len]);
					dp[l][r][pre]=res;
				}
			}
		}
		printf("%d\n", dp[0][p-1][seg[0].len]);
	}
} 

