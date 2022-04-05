                 #include <iostream>

                 #include <algorithm>
				 using namespace std;
                 const int INF=1000000000;

                  

                 struct Edge{

                       int start,stop;

                       int weight;

                 };

                 #define N 30

                 int nn,s,num;

                 int graph[N][N];

                 char name[30][15];

                 Edge mst[N];

                 bool Find,use[30];

                  

                 int get(char* s)

                 {

                         for(int i=0;i<num;i++)

                                if(strcmp(name[i],s)==0) return i;

                         strcpy(name[num],s);

                         num++;

                         return num-1;

                 }

                  

                 int prim(){

                       int result=0;

                       int i,j,min,vx,vy;

                       int weight,minweight;

                       for(i=1;i<nn-1;i++){

                             mst[i].start=1;

                             mst[i].stop=i+1;

                             mst[i].weight=graph[1][i+1];

                       }

                       for(i=1;i<nn-1;i++){

                             minweight=INF+1;min=-1;

                             for(j=i;j<nn-1;j++)

                                   if(mst[j].weight<minweight)

                                         minweight=mst[j].weight,min=j;

                             if(min==-1)break;

                             std::swap(mst[min],mst[i]);

                             result+=minweight;

                             vx=mst[i].stop;

                             for(j=i+1;j<nn-1;j++){

                                   vy=mst[j].stop;

                                   weight=graph[vx][vy];

                                   if(weight<mst[j].weight)

                                         mst[j].weight=weight,mst[j].start=vx;

                             }

                       }

                       return result;

                 }

                  

                 void cycle(int x,int begin,int &max,int last,int &c)

                 {

                         int i;

                         if(x==begin)

                         {

                                Find=true;

                                return;

                         }

                         for(i=0;i<nn-1;i++)

                         {

                                if(mst[i].start!=x&&mst[i].stop!=x) continue;

                                if(mst[i].start==x&&mst[i].stop!=last)

                                {

                                        cycle(mst[i].stop,begin,max,x,c);

                                        if(Find)

                                        {

                                                if(max<mst[i].weight&&mst[i].stop!=0)

                                                       max=mst[i].weight,c=i;

                                                return ;

                                        }

                                } else if(mst[i].stop==x&&mst[i].start!=last)

                                {

                                        cycle(mst[i].start,begin,max,x,c);

                                        if(Find)

                                        {

                                                if(max<mst[i].weight&&mst[i].start!=0)

                                                       max=mst[i].weight,c=i;

                                                return ;

                                        }

                                }

                         }

                 }

                  

                        

                 int main()

                 {

                         int n,i,x,y,j,min,temp,max,c,temp0;

                         char name1[15],name2[15];
                       //  freopen("1639.in","r",stdin);

                         cin>>n;

                         num=1;

                         strcpy(name[0],"Park");

                         for(i=0;i<25;i++)

                                for(j=0;j<25;j++)

                                        graph[i][j]=INF;

                         for(i=0;i<n;i++)

                         {

                                cin>>name1>>name2;

                                x=get(name1);

                                y=get(name2);

                                cin>>graph[x][y];

                                graph[y][x]=graph[x][y];

                         }

                         nn=num;

                         cin>>s;

                         int r=prim();

                         min=INF+1;

                         for(i=1;i<nn;i++)

                         {

                                use[i]=false;

                                if(graph[0][i]<min)

                                {

                                        min=graph[0][i];

                                        temp=i;

                                }

                         }

                         use[temp]=true;

                         r+=min;

                         mst[0].start=0;

                         mst[0].stop=temp;

                         mst[0].weight=min;

                         for(i=1;i<s;i++)

                         {

                                min=INF+1;

                                temp=-1;temp0=-1;

                                for(j=1;j<nn;j++)

                                {

                                        if(use[j]) continue;

                                        Find=false;

                                        max=0;

                                        cycle(j,0,max,0,c);

                                        if(graph[0][j]-max<min)

                                        {

                                                min=graph[0][j]-max;

                                                temp=c;

                                                temp0=j;

                                        }

                                }

                                if(min>=0) break;

                                if(temp!=-1){

                                        mst[temp].start=0;

                                        mst[temp].stop=temp0;

                                        mst[temp].weight=graph[0][temp0];

                                }

                                 use[j]=true;

                                r+=min;

                         }

                  

                  

                         cout<<"Total miles driven: "<<r<<endl;
                         
                     //    while(i=1);

                         return 0;

                 }
