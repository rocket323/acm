#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 5010

struct node
{
	int a, b;
}
E[maxl];

int n, m, ans;

bool cmp(node A, node B) {
	return A.a < B.a;
}

int main()
{
	while(scanf("%d%d", &n, &m), (n + m)) {
		for(int i=0; i<m; ++i) scanf("%d%d", &E[i].a, &E[i].b);
		sort(E, E + m, cmp);

		ans = n + 1;
		for(int i=0; i<m; ++i) {
			ans -= E[i].b - E[i].a + 1;
			if(i && E[i].a == E[i-1].b) ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
