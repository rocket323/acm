#include<stdio.h>
#include<vector>
#include <cstring>
#include<algorithm>
using namespace std;
vector<long>v[1100];
long n,m;
long map[1100][1100],color[1100],dfn[1100],low[1100],cnt,com;
long father[1100],stack[21000],top;
struct comp
{
       long count;
       long element[1100];
}p[1100];
void dfs(long cur,long fa)
{
     long len=v[cur].size(),i,j,tv;
     low[cur]=dfn[cur]=cnt++;
     stack[++top]=cur;
     for(i=0;i<len;i++)
     {
         tv=v[cur][i];
          if(!dfn[tv])
          {
             dfs(tv,cur);
             if(low[cur]>low[tv])
               low[cur]=low[tv];
             if(low[tv]>=dfn[cur])
             {
                p[com].element[p[com].count++]=cur;
               do
               {
                p[com].element[p[com].count++]=stack[top];
               }while(stack[top--]!=tv);
               com++;
             }
          }
          else if(fa!=tv)
          {
             if(low[cur]>dfn[tv])
               low[cur]=dfn[tv];
              
          }
     }
}
void biconnect()
{
     long i,j;
     for(i=0;i<=n;i++)
      p[i].count=0;
     for(i=0;i<=n;i++)
      dfn[i]=0;
      cnt=1;
      com=1;
      top=0;
      for(i=1;i<=n;i++) if(!dfn[i])
       dfs(i,i);
}
long findfather(long cur)
{
     if(cur==father[cur]) return cur;
     father[cur]=findfather(father[cur]);
     return father[cur];
}
void uni(long x,long y)
{
     long fx=findfather(x);
     long fy=findfather(y);
     father[fx]=fy;
}
bool judge(long index)
{
     long i,j,ts[1100],a,b;
     struct comp tmp=p[index];
     for(i=1;i<=n;i++)
     {
        father[i]=i;
        ts[i]=0;
     }
     for(i=0;i<tmp.count;i++)
      for(j=i+1;j<tmp.count;j++) if(map[tmp.element[i]][tmp.element[j]])
      {
        a=tmp.element[i];
        b=tmp.element[j];
         if(findfather(a)==findfather(b)) return 1;
         if(ts[a])
         uni(ts[a],b);
         if(ts[b])
         uni(a,ts[b]);
         ts[a]=b;
         ts[b]=a;
      }
     return 0;
}
int main()
{
    long i,j,x,y,ans;
    while(EOF!=scanf("%ld%ld",&n,&m))
    {
     if(n==0&&m==0) break;
      for(i=0;i<=n;i++)
       for(j=0;j<=n;j++)
       map[i][j]=1;
        for(i=1;i<=m;i++)
        {
          scanf("%ld%ld",&x,&y);
          map[x][y]=0;
          map[y][x]=0;
        }
        for(i=1;i<=n;i++)
        {
          v[i].clear();
          for(j=1;j<=n;j++) if(map[i][j]&&i!=j)
           v[i].push_back(j);
        }
        biconnect();
          memset(color,0,sizeof(color));
          ans=0;
        for(i=1;i<=com;i++)
        if(judge(i)&&p[i].count>1)
        {
             for(j=0;j<p[i].count;j++) if(!color[p[i].element[j]])
             {
              color[p[i].element[j]]=1;
              ans++;
             }
        }
        printf("%ld\n",n-ans);
    }
    return 0;
}