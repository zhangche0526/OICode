/**************************************************************
    Problem: 3996
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:1720 ms
    Memory:29164 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using std::min;
 
const int MAXV=3e5+5,MAXE=1e6+5,INF=1061109567;
 
int S,T;
 
struct E{int next,to,cap;} e[MAXE<<1];int ecnt,G[MAXV];
void addEdge(int u,int v,int c)
{
    e[++ecnt]=(E){G[u],v,c};G[u]=ecnt;
    e[++ecnt]=(E){G[v],u,0};G[v]=ecnt;
}
 
std::queue<int> que;
int dpt[MAXV];
bool calDpt()
{
    memset(dpt,-1,sizeof dpt);
    dpt[S]=0,que.push(S);
    while(!que.empty())
    {
        int u=que.front();que.pop();
        for(int i=G[u];i;i=e[i].next) if(e[i].cap>0)
        {
            int v=e[i].to;
            if(~dpt[v]) continue;
            dpt[v]=dpt[u]+1;
            que.push(v);
        }
    }
    return ~dpt[T];
}
 
int iter[MAXV];
int calF(int u,int f)
{
    if(u==T) return f;
    for(int &i=iter[u];i;i=e[i].next) if(e[i].cap>0)
    {
        int v=e[i].to;
        if(dpt[v]!=dpt[u]+1) continue;
        int res=calF(v,min(f,e[i].cap));
        if(res)
        {
            e[i].cap-=res,e[i^1].cap+=res;
            return res;
        }
    }
    return 0;
}
 
int maxFlow()
{
    int f,res=0;
    while(calDpt())
    {
        memcpy(iter,G,sizeof G);
        while(f=calF(S,INF)) res+=f;
    }
    return res;
}
 
int n;
 
int main()
{
    int i,j,x;scanf("%d",&n);
    int ans=0;S=n*(n+1)+1,T=S+1;
    for(i=1;i<=n;i++) for(j=1;j<=n;j++)
    {
        scanf("%d",&x);ans+=x;
        addEdge(S,i*n+j,x);
        addEdge(i*n+j,i,INF);
        addEdge(i*n+j,j,INF);
    }
    for(i=1;i<=n;i++)
    {
        scanf("%d",&x);
        addEdge(i,T,x);
    }
    ans-=maxFlow();
    printf("%d",ans);
    return 0;
}
?
