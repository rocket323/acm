#include <cmath>
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
 //N (2 <= N <= 1000)
#define min(a,b) ((a)<(b)?(a):(b))

struct Point3D
{
 Point3D()
 {
  x=y=z=0;
 }
 void set(int _x,int _y,int _z)
 {
  x=_x;y=_y;z=_z;
 }
 double len(const Point3D& pt) const
 {
  int dx=x-pt.x;
  int dy=y-pt.y;
  return sqrt((double)(dx*dx+dy*dy));
 }
 int cost(const Point3D& pt) const 
 {
  return abs(z-pt.z);
 }
 int x,y,z;
};
struct Edge
{
 Edge(int _pt1,int _pt2)
 {
  pt1=_pt1;pt2=_pt2;
 }
 int pt1,pt2;
};

const int MAXN=1001;
const int INF=0xfffff;
int N;
Point3D vil[MAXN];
//用于Prim算法
double dLowCost[MAXN];//外面某村庄到closet中的各村庄的最小值
int nToIdx[MAXN];//最小消耗所对应的村庄
char closet[MAXN]={0};//已选进来的村庄
vector<Edge> vecEdge;//建立的边

inline double GetCost(double dRate,const Point3D& pt1,const Point3D& pt2)
{
 return pt1.cost(pt2)-dRate*pt1.len(pt2);
}
//返回下一个要加入的节点下标
int RefLowCost(int id,double dRate)
{
 double dMinCost=INF;
 int nMinIdx=-1;
 for (int i=0;i<N;i++)
 {
  if(!closet[i])
  {
   double dCost=GetCost(dRate,vil[id],vil[i]);
   if(dCost<dLowCost[i])
   {
    dLowCost[i]=dCost;
    nToIdx[i]=id;
   }
   if (dLowCost[i]<dMinCost)
   {
    dMinCost=dLowCost[i];
    nMinIdx=i;
   }
  }
 }
 return nMinIdx;
}

void Prim(double dRate)
{
 int i;
 //////////////////////////////////////////////////////////////////////////
 //初始化
 vecEdge.clear();
 memset(closet,0,sizeof(closet));
 for (i=1;i<N;i++)
 {
  dLowCost[i]=INF;
  nToIdx[i]=-1;
 }
 //////////////////////////////////////////////////////////////////////////
 closet[0]=1;
 int nMinIdx=0;
 for (i=1;i<N;i++)
 {
  int nNex=RefLowCost(nMinIdx,dRate);
  closet[nNex]=1;
  vecEdge.push_back(Edge(nToIdx[nNex],nNex));
  nMinIdx=nNex;
 }
}

//////////////////////////////////////////////////////////////////////////
//迭代法
double GetRate()
{
 double dC=0,dL=0;
 for (int i=0;i<vecEdge.size();i++)
 {
  dC+=vil[vecEdge[i].pt1].cost(vil[vecEdge[i].pt2]);
  dL+=vil[vecEdge[i].pt1].len(vil[vecEdge[i].pt2]);
 }
 return dC/dL;
}
double ItSolve()
{
 double dNexRate=0;
 double dRate;
 do
 {
  dRate=dNexRate;
  Prim(dRate);
  dNexRate=GetRate();
 }while(fabs(dRate-dNexRate)>1e-6);
 return dRate;
}
int main(int argc, char* argv[])
{
 vecEdge.reserve(999);
 while (scanf("%d",&N)&&N)
 {
  for (int i=0;i<N;i++)
  {
   int x,y,z;
   scanf("%d%d%d",&x,&y,&z);
   vil[i].set(x,y,z);
  }
  printf("%.3lf\n",ItSolve());
 }
 return 0;
}