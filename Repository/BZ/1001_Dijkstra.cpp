/**************************************************************
    Problem: 1001
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:2064 ms
    Memory:89184 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
 
const int MAXV=2e6+105,MAXE=3e6+5,INF=~0U>>1;
 
int N,M,S,T;
 
struct E{int next,to,val;} e[MAXE<<1];int ecnt,G[MAXV];
void addEdge(int u,int v,int w)//双向边
{
    e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;
    e[++ecnt]=(E){G[v],u,w};G[v]=ecnt;
}
 
struct HN
{
    int id,v;
    bool operator<(const HN & ot)const
    {return v>ot.v;}
};
 
priority_queue<HN> heap;
bool inS[MAXV];int dis[MAXV];
int dijkstra()
{
    int i;
    for(i=1;i<=T;i++) dis[i]=INF;
    dis[S]=0;heap.push((HN){S,0});
    while(!heap.empty())
    {
        int u=heap.top().id;heap.pop();
        if(inS[u]) continue;
        inS[u]=true;
        for(i=G[u];i;i=e[i].next)
        {
            int v=e[i].to;
            if(inS[v]) continue;
            if(dis[v]>dis[u]+e[i].val)
            {
                dis[v]=dis[u]+e[i].val;
                heap.push((HN){v,dis[v]});
            }
        }
    }
    return dis[T];
}
 
int main()
{
    int i,j,w;
    scanf("%d%d",&N,&M);
    if(N==1||M==1)
    {
        if(N>M) swap(N,M);
        int ans=INF;
        for(i=1;i<=M;i++)
            scanf("%d",&w),ans=min(ans,w);
        printf("%d\n",ans);
    }else
    {
        S=2*(N-1)*(M-1)+1,T=S+1;
        //读取横向
        for(i=1;i<M;i++)
        {int v=i*2;scanf("%d",&w);addEdge(S,v,w);}
        for(i=2;i<N;i++)
            for(j=1;j<M;j++)
            {int u=2*((i-2)*(M-1)+j)-1,v=2*((i-1)*(M-1)+j);scanf("%d",&w);addEdge(u,v,w);}
        for(i=1;i<M;i++)
        {int u=2*((N-2)*(M-1)+i)-1;scanf("%d",&w);addEdge(u,T,w);}
        //读取纵向
        for(i=1;i<N;i++)
            for(j=1;j<=M;j++)
            {
                scanf("%d",&w);
                if(j==1)
                {int u=2*((i-1)*(M-1)+j)-1;addEdge(u,T,w);}
                else if(j==M)
                {int v=2*((i-1)*(M-1)+j-1);addEdge(S,v,w);}
                else
                {int u=2*((i-1)*(M-1)+j-1),v=u+1;addEdge(u,v,w);}
            }
        //读取斜向
        for(i=1;i<N;i++)
            for(j=1;j<M;j++)
            {int u=2*((i-1)*(M-1)+j)-1,v=u+1;scanf("%d",&w);addEdge(u,v,w);}
        printf("%d\n",dijkstra());
    }
    return 0;
}
/*
 *  ---------
 *  |1\2|3\4|
 *  |---|---|
 *  |5\6|7\8|
 *  |---|---|
 */
