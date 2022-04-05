#include <stdio.h>
#include <string.h>

#define VMAX 500
#define PMAX 500
#define CL 30

int n, d, k, no;
char plug[PMAX][CL];
int mapade[PMAX][PMAX],dev[VMAX];

void warshall()
{
	int i, j, m;

	for(i = 0; i < no; i++)
	{
		for(j = 0; j < no; j++)
			if(mapade[j][i])
				for(m = 0; m < no; m++)
					if(mapade[i][m])mapade[j][m]=1;
	}
}


int addplug(char plu[CL])
{
	int i;
	for(i=0;i<no;i++)if(strcmp(plug[i],plu)==0)return i;
	strcpy(plug[no],plu);no++;
	return no-1;
}

void bypart(int map[VMAX][VMAX],int cou, int stu)
{

	int i,i1,i2,num,num1,que[VMAX],match1[VMAX],match2[VMAX],pque,p1,now,prev[VMAX],x,y;

	num=0;
	memset(match1,-1,sizeof(match1));
	memset(match2,-1,sizeof(match2));
	for(i1=0;i1<cou;i1++)
	{
		p1=0;
		pque=0;
		for(i2=0;i2<stu;i2++)
		{
			if(map[i1][i2])
			{
				prev[i2]=-1;
				que[pque++]=i2;
			}
			else prev[i2]=-2;
		}
		while(p1<pque)
		{
			now=que[p1];
			if(match2[now]==-1)
				break;
			p1++;
			for(i2=0;i2<stu;i2++)
			{
				if(prev[i2]==-2&&map[match2[now]][i2])
				{
					prev[i2]=now;
					que[pque++]=i2;
				}
			}
		}
		if(p1==pque)continue;
		while(prev[now]>=0)
		{
			match1[match2[prev[now]]]=now;
			match2[now]=match2[prev[now]];
			now=prev[now];
		}
		match2[now]=i1;
		match1[i1]=now;
		num++;
	}
	printf("%d\n",cou-num);  
}

void input()
{
	int n1, n2;
	int i, j, m;
	int map[VMAX][VMAX];
	char tmp1[CL],tmp2[CL];

	scanf("%d",&n);
	memset(map,0,sizeof(map));
	memset(mapade,0,sizeof(map));

	for(i = 0; i < n; i++)scanf("%s",plug[i]);
	no=n;

	scanf("%d",&d);
	for(i = 0; i < d; i++)
	{
		scanf("%s%s",tmp1,tmp2);
		dev[i]=addplug(tmp2);
	}

	scanf("%d",&k);
	for(i = 1; i <= k; i++)
	{
		scanf("%s%s",tmp1,tmp2);
		n1=addplug(tmp1);n2=addplug(tmp2);
		mapade[n1][n2]=1;
	}
	for(i=0;i<no;i++)mapade[i][i]=1;

	warshall();

	for(i=0;i<d;i++)
		for(j=0;j<n;j++)if(mapade[dev[i]][j])map[i][j]=1;

	bypart(map,d,n);
}

int main()
{
	input();
	return 1;
}
