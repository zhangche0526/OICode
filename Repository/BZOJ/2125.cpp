/**************************************************************
    Problem: 2125
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:432 ms
    Memory:21816 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<stack> 
#include<queue>
 
const int MAXN=1e4+5;
 
int N,M,Q;
 
int abs(int x){return (x<0)?(-x):x;}
 
struct E{int next,to,val;} e[MAXN<<3];int ecnt,G[MAXN];
void addEdge(int u,int v,int w){e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;}
void addEdge2(int u,int v,int w){addEdge(u,v,w);addEdge(v,u,w);}
void initCFS(){memset(G,0,sizeof(G));ecnt=0;}
struct A{int u,v,w;A(int u=0,int v=0,int w=0):u(u),v(v),w(w){};};
 
int dis[MAXN];bool inQ[MAXN];
std::queue<int> que;
void SPFA(int S)
{
    int i;
    memset(dis,0x3f,sizeof(dis));
    que.push(S);dis[S]=0;inQ[S]=true;
    while(!que.empty())
    {
        int u=que.front();que.pop();
        inQ[u]=false;
        for(i=G[u];i;i=e[i].next)
        {
            int v=e[i].to;
            if(dis[v]>dis[u]+e[i].val)
            {
                dis[v]=dis[u]+e[i].val;
                if(!inQ[v]) que.push(v),inQ[v]=true;
            }
        }
    }
}

std::stack<A> st;
int ringLen[MAXN],rcnt;
int belong[MAXN],ringRtDis[MAXN];
int anc[MAXN][20];
void addRing(int u,int v)
{
    rcnt++;
    while(st.top().u!=u&&st.top().v!=v)
    {
        A a=st.top();st.pop();
        ringRtDis[a.u]=ringRtDis[a.v]+a.w;
        ringLen[rcnt]+=a.w;
        if(a.u!=u) belong[a.u]=rcnt,anc[a.u][0]=u;
        if(a.v!=u) belong[a.v]=rcnt,anc[a.v][0]=u;
    }
    A a=st.top();st.pop();
    ringRtDis[a.u]=ringRtDis[a.v]+a.w;
    ringLen[rcnt]+=a.w;
    anc[a.v][0]=a.u;
}

int dfn[MAXN],low[MAXN],dcnt;
void tarjan(int u,int la)
{
    dfn[u]=low[u]=++dcnt;
    for(int i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==la) continue;
        if(!dfn[v])
        {
            st.push(A(u,v,e[i].val));
            tarjan(v,u);
            low[u]=std::min(low[u],low[v]);
            if(low[v]>=dfn[u])
                addRing(u,v);
        }else if(dfn[v]<low[u]) low[u]=dfn[v],st.push(A(u,v,e[i].val));
    }
}

int dpt[MAXN];
int rebuild(int u,int la)
{
    dpt[u]=dpt[la]+1;
    for(int i=G[u];i;i=e[i].next)
        rebuild(e[i].to,u);
}

inline void initLCA()
{
    for(int i=1;(1<<i)<=N;i++)
        for(int j=1;j<=N;j++)
            anc[j][i]=anc[anc[j][i-1]][i-1];
}

int calDis(int x,int y)
{
    int i;
    if(dpt[x]<dpt[y]) std::swap(x,y);
    int xDis=dis[x],yDis=dis[y];
    int maxlogn=std::floor(std::log(N)/std::log(2));
    for(i=maxlogn;i>=0;i--)
        if(dpt[x]-(1<<i)>=dpt[y])
            x=anc[x][i];
    if(x==y) return xDis-dis[x];
    for(i=maxlogn;i>=0;i--)
        if(anc[x][i]!=anc[y][i])
            x=anc[x][i],y=anc[y][i];
    if(belong[x]&&belong[x]==belong[y])
    {
        int xyDis=abs(ringRtDis[x]-ringRtDis[y]);
        int minDis=std::min(xyDis,ringLen[belong[x]]-xyDis);
        return xDis+yDis-dis[x]-dis[y]+minDis;
    }else return xDis+yDis-2*dis[anc[x][0]];
}

int main()
{   
    int i;
    scanf("%d%d%d",&N,&M,&Q);
    for(i=1;i<=M;i++)
    {
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        addEdge2(u,v,w);
    }
    SPFA(1);
    tarjan(1,0);
    initLCA();
    initCFS();
    for(i=2;i<=N;i++)
        addEdge(anc[i][0],i,0);
    rebuild(1,0);
    while(Q--)
    {
        int x,y;scanf("%d%d",&x,&y);
        printf("%d\n",calDis(x,y));
    }
    return 0;
}
