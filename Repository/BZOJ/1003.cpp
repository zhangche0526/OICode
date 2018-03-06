/**************************************************************
    Problem: 1003
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:40 ms
    Memory:1352 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
 
const int MAXN=105,MAXV=25,MAXE=MAXV*MAXV,INF=~0U>>5;
 
int n,m,K,en,d;
bool ban[MAXV][MAXN];//第i个码头在第j天是否被禁
 
struct E{int next,to,val;} e[MAXE<<1];int ecnt,G[MAXV];
void addEdge(int u,int v,int w)
{
    e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;
    e[++ecnt]=(E){G[v],u,w};G[v]=ecnt;
}
 
int cost[MAXN][MAXN];
int dp[MAXN];
 
bool cantuse[MAXV];
int dis[MAXV];bool inS[MAXV];
struct HN
{
    int id,v;
    bool operator < (const HN & ot)const
    {return v>ot.v;}
};
priority_queue<HN> heap;
int dijkstra()
{
    int i;
    for(i=1;i<=m;i++) dis[i]=INF;
    memset(inS,false,sizeof(inS));
    dis[1]=0;heap.push((HN){1,0});
    while(!heap.empty())
    {
        int u=heap.top().id;heap.pop();
        if(inS[u]) continue;
        inS[u]=true;
        for(i=G[u];i;i=e[i].next)
        {
            int v=e[i].to;
            if(inS[v]||cantuse[v]) continue;
            if(dis[v]>dis[u]+e[i].val)
            {
                dis[v]=dis[u]+e[i].val;
                heap.push((HN){v,dis[v]});
            }
        }
    }
    return dis[m];
}
int main()
{
    int i,j,x,t;
    scanf("%d%d%d%d",&n,&m,&K,&en);
    for(i=1;i<=en;i++)
    {
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
    }
    scanf("%d",&d);
    for(i=1;i<=d;i++)
    {
        int P,l,r;scanf("%d%d%d",&P,&l,&r);
        for(j=l;j<=r;j++) ban[P][j]=true;
    }
    for(i=1;i<=n;i++)
        for(j=i;j<=n;j++)
        {
            memset(cantuse,false,sizeof(cantuse));
            for(x=2;x<m;x++)
                for(t=i;t<=j;t++)
                    if(ban[x][t])
                    {cantuse[x]=true;break;}
            cost[i][j]=dijkstra();
            if(cost[i][j]!=INF) cost[i][j]*=j-i+1;
        }
    for(i=1;i<=n;i++) dp[i]=INF;
    dp[0]=-K;
    for(i=1;i<=n;i++)
        for(j=0;j<i;j++)
            dp[i]=min(dp[i],dp[j]+cost[j+1][i]+K);
    printf("%d\n",dp[n]);
}
