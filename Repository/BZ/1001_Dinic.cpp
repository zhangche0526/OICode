/**************************************************************
    Problem: 1001
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:2876 ms
    Memory:153636 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
  
const int MAXV=1e6+5,MAXE=3e6+5,INF=~0U>>1;//6
  
int N,M,S,T;
  
struct E{int next,to,cap;} e[MAXE<<2];
int ecnt=1,G[MAXV];
void addEdge(int u,int v,int c)
{
    e[++ecnt]=(E){G[u],v,c};G[u]=ecnt;
    e[++ecnt]=(E){G[v],u,0};G[v]=ecnt;
}
int dfn[MAXV];
queue<int> que;
bool calDfn()
{
    int i;
    memset(dfn,-1,sizeof(dfn));
    dfn[S]=0;que.push(S);
    while(!que.empty())
    {
        int u=que.front();que.pop();
        for(i=G[u];i;i=e[i].next)
        {
            int v=e[i].to;
            if(e[i].cap>0&&dfn[v]==-1)
                dfn[v]=dfn[u]+1,que.push(v);
        }
    }
    return dfn[T]!=-1;
}
int iter[MAXV];
int calF(int u,int f)
{
    if(u==T) return f;
    for(int & i=iter[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(e[i].cap>0&&dfn[v]==dfn[u]+1)
        {
            int res=calF(v,min(f,e[i].cap));
            if(res>0)
            {
                e[i].cap-=res,e[i^1].cap+=res;
                return res;
            }
        }
    }
    return 0;
}
int dinic()
{
    int i,f,res=0;
    while(calDfn())
    {
        for(i=1;i<=N*M;i++) iter[i]=G[i];
        while((f=calF(S,INF))>0) res+=f;
    }
    return res;
}
int main()
{
    int i,j,u,v,c;
    scanf("%d%d",&N,&M);
    S=1,T=N*M;
    for(i=1;i<=N;i++)
        for(j=1;j<M;j++)
        {
            u=j+(i-1)*M,v=u+1;scanf("%d",&c);
            addEdge(u,v,c);addEdge(v,u,c);
        }
    for(i=1;i<N;i++)
        for(j=1;j<=M;j++)
        {
            u=j+(i-1)*M,v=u+M;scanf("%d",&c);
            addEdge(u,v,c);addEdge(v,u,c);
        }
    for(i=1;i<N;i++)
        for(j=1;j<M;j++)
        {
            u=j+(i-1)*M,v=u+M+1;scanf("%d",&c);
            addEdge(u,v,c);addEdge(v,u,c);
        }
    printf("%d\n",dinic());
    return 0;
}

