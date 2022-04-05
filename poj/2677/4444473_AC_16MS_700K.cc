#include <iostream>
#include <algorithm>
#define MaxL 1e24
#include <cmath>
using namespace std;

struct node{
	double x, y;
}P[1002];

int N;
double f[1002][1002];

bool cmp(node A, node B){ return A.x<B.x; }
double Min(double a, double b){ return (a<b)?a:b; }

double dis(int i, int j)
{
	return sqrt((P[i].x-P[j].x)*(P[i].x-P[j].x)+(P[i].y-P[j].y)*(P[i].y-P[j].y));
}

void init()
{
    for(int i=1; i<=N; ++i)
    	cin>>P[i].x>>P[i].y;
    sort(P+1, P+N, cmp);
}

void process()
{
	int i,j,k;
	for(i=1; i<=N; ++i)
	{
		for(j=1; j<i; ++j)
		{
			if(j==1)
			{
				f[i][j] = f[i-1][j]+dis(i-1, i);
			}
			else if(j<i-1)
			{
				f[i][j] = f[i-1][j] + dis(i-1, i);
			}
			else if(j==i-1)
			{
				double tmp = MaxL;
				for(k=1; k<j; ++k)
					if(tmp>f[j][k]+dis(k, i))
						tmp=f[j][k]+dis(k, i);
				f[i][j] = tmp;
			}
		}
		
		/*rec = MaxL;
		for(j=1; j<i; ++j)
			rec = Min(rec, f[i][j]+dis(j, i+1));*/
	}
	double res = MaxL;
	for(i=1; i<N; ++i)
		if(res>f[N][i]+dis(i, N))
			res = f[N][i]+dis(i, N);
	printf("%.2f\n", res);
}

int main()
{
	while(cin>>N)
	{	
    	init();
    	process();
	}
    return 0;
}
