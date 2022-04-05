#include <stdio.h>
#include <cstring>
#define INF 0x7fffffff

int a[16][3], b[3], k;

int dis(int k)
{
	int ans = 0;
	for(int i=0; i<3; ++i) ans += (a[k][i] - b[i]) * (a[k][i] - b[i]);
	return ans;
}

int main()
{
	for(int i=0; i<16; ++i)
	{
		for(int j=0; j<3; ++j) scanf("%d", &a[i][j]);
	}

	while(scanf("%d%d%d", &b[0], &b[1], &b[2]), b[0]!=-1)
	{
		int tmp = INF;
		for(int i=0; i<16; ++i)
		{
			if(dis(i) < tmp)
			{
				k = i;
				tmp = dis(i);
			}
		}
		printf("(%d,%d,%d) maps to (%d,%d,%d)\n", b[0], b[1], b[2], a[k][0], a[k][1], a[k][2]);
	}
	return 0;
}
