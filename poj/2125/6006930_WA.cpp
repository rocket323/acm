#include<stdio.h>
#include<string.h>
#define maxn 220
#define inf 0x7fffffff
int G[maxn][maxn];
int f[maxn][maxn];
bool flag[maxn];
int v[maxn],q[maxn];
int pre[maxn];
int s,t;
int n,m;

#define insert(f,t,p) G[f][t]+=p

void init()
{
	s=0,t=1;
	int tmp;
	memset(G,0,sizeof(G));
	for(int i=0;i<n;++i)
	{
		scanf("%d",&tmp);
		insert(i+i+3,t,tmp);
	}
	for(int i=0;i<n;++i)
	{
		scanf("%d",&tmp);
		insert(s,i+i+2,tmp);
	}
	tmp=1000000000;
	int from,to;
	for(int i=0;i<m;++i)
	{
		scanf("%d%d",&from,&to);
		insert(from+from,to+to+1,tmp);
		insert(to+to+1,from+from,tmp);
	}
}

#define fmin(a,b) ((a)<(b)?(a):(b))

int solve(int s,int t,int n)
{
	memset(f,0,sizeof(f));
	while(1)
	{
		int head=0,end=0;
		memset(flag,0,sizeof(flag));
		v[s]=inf;
		q[head++]=s;
		pre[s]=s;
		flag[s]=1;
		while(head>end&&!flag[t])
		{
			int tmp=q[end++];
			for(int i=0;i<n;++i)
				if(!flag[i])
				{
					if(G[tmp][i]>f[tmp][i])
					{
						flag[i]=1;
						q[head++]=i;
						pre[i]=tmp;
						v[i]=fmin(v[tmp],G[tmp][i]-f[tmp][i]);
					}
					else if(f[i][tmp]>0)
					{
						flag[i]=1;
						q[head++]=i;
						pre[i]=-tmp;
						v[i]=fmin(f[i][tmp],v[tmp]);
					}
				}
		}
		if(!flag[t])
			break;
		int tmp=t;
		while(tmp!=s)
		{
			int tmp1=pre[tmp];
			if(tmp1>=0) f[tmp1][tmp]+=v[t];
			else f[tmp][-tmp1]-=v[t];
			tmp=tmp1;
			if(tmp<0) tmp=-tmp;
		}
	}
	int re=0;
	for(int i=0;i<n;++i)
		re+=f[s][i];
	return re;
}

void output()
{
	memset(flag,0,sizeof(flag));
	int head=0,end=0;
	int p;
	q[head++]=s;
	flag[s]=1;
	while(head>end)
	{
		p=q[end++];
		for(int i=0;i<n+n+2;++i)
			if((G[p][i]>f[p][i]||f[i][p]>0)&&!flag[i])
			{
		//		printf("%d\t%d\n",p,i);
				flag[i]=1;
				q[head++]=i;
			}
	}
	int ans=0;
	for(int i=0;i<n;++i)
	{
		if(!flag[i+i+2]) ++ans;
		if(flag[i+i+3]) ++ans;
	}
	printf("%d\n",ans);
	for(int i=0;i<n;++i)
	{
		if(!flag[i+i+2]) printf("%d -\n",i+1);
		if(flag[i+i+3]) printf("%d +\n",i+1);
	}
}

int main()
{
	while(scanf("%d%d",&n,&m)==2)
	//scanf("%d%d",&n,&m);
	{
		init();
		printf("%d\n",solve(s,t,n+n+2));
		output();
	}
	return 0;
}

