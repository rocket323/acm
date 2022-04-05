＃i nclude<cstdio>
＃i nclude<cmath>
#define oo 10000000
#define min(a,b) (a<b?a:b)

int map[8][8];
double C[16][8][8][8][8];
double ans;
int n;

double caluate(int i1,int j1,int i2,int j2)
{
    double sum=0;
    int i,j;
    for(i=i1;i<=i2;i++)
    {
        for(j=j1;j<=j2;j++)
        {
            sum+=map[i][j];
        }
    }
    return sum;
}


void dp(int m,int si,int sj,int ei,int ej) //
{
    int i,j;
    double sum,mins=oo;
    for(j=sj;j<ej;j++)
    {
            mins=min(mins,C[1][si][sj][ei][j]+C[m-1][si][j+1][ei][ej]);
            mins=min(mins,C[m-1][si][sj][ei][j]+C[1][si][j+1][ei][ej]);
    }
    for(i=si;i<ei;i++)
    {
            mins=min(mins,C[1][si][sj][i][ej]+C[m-1][i+1][sj][ei][ej]);
            mins=min(mins,C[m-1][si][sj][i][ej]+C[1][i+1][sj][ei][ej]);
    }
    C[m][si][sj][ei][ej]=mins;
}

void input()
{
    int i,j;
    double sum=0;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            scanf("%d",&map[i][j]);
            sum+=map[i][j];
        }
    }
    ans=sum/double(n);
}

void reset()
{
    int i,j,k,l,m;
    for(m=0;m<=n;m++)
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            for(k=0;k<8;k++)
            {
                for(l=0;l<8;l++)
                {
                    C[m][i][j][k][l]=0;
                }
            }
        }
    }
}

int main()
{
    int m,i,j,k,l;
    while(scanf("%d",&n)!=EOF)
    {
        input();
        reset();

        for(m=1;m<=n;m++)
        for(i=0;i<8;i++)
        {
            for(j=0;j<8;j++)
            {
                for(k=0;k<8;k++)
                {
                    for(l=0;l<8;l++)
                    {
                        if((k-i+1)*(l-j+1)<m)
                            C[m][i][j][k][l]=oo;
                        else
                        {
                            if(m==1)
                            {
                                C[m][i][j][k][l]=pow((caluate(i,j,k,l)-ans),2);
                            }
                            else
                            {
                                dp(m,i,j,k,l);
                            }
                        }
                    }
                }
            }
        }
        printf("%.3lf\n",sqrt(C[n][0][0][7][7]/n));
    }
    return 0;
}