/**************************************************************
    Problem: 4316
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:208 ms
    Memory:12144 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
  
const int MAXN=2e5+5,MAXM=2e5+5,INF=~0U>>1;
  
int n,m,newn;//newn：圆方树的点数
  
struct CFS
{
    struct E{int next,to;} e[MAXM];int ecnt,G[MAXN];
    void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
    void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}
    CFS(){ecnt=1;}
} G,T;
  
int f[MAXN][2],g[MAXN][2],gcnt;
void treeDP(int u,int from)
{
    int i;
    if(u<=n)
    {
        f[u][0]=0;f[u][1]=1;
        for(i=T.G[u];i;i=T.e[i].next)
        {
            int v=T.e[i].to;
            if(v==from) continue;
            treeDP(v,u);
            if(v>n) continue;
            f[u][0]+=std::max(f[v][0],f[v][1]);
            f[u][1]+=f[v][0];
        }
    }
    else
    {
        for(i=T.G[u];i;i=T.e[i].next)
            if(T.e[i].to!=from)
                treeDP(T.e[i].to,u);
        gcnt=0;
        for(i=T.G[u];i;i=T.e[i].next)
        {
            g[++gcnt][0]=f[T.e[i].to][0];
            g[gcnt][1]=f[T.e[i].to][1];
        }
        for(i=gcnt-1;i;i--)
        {
            g[i][0]+=std::max(g[i+1][0],g[i+1][1]);
            g[i][1]+=g[i+1][0];
        }
        f[from][0]=g[1][0];
        gcnt=0;
        for(i=T.G[u];i;i=T.e[i].next)
        {
            g[++gcnt][0]=f[T.e[i].to][0];
            g[gcnt][1]=f[T.e[i].to][1];
        }
        g[gcnt][1]=-INF;
        for(i=gcnt-1;i;i--)
        {
            g[i][0]+=std::max(g[i+1][0],g[i+1][1]);
            g[i][1]+=g[i+1][0];
        }
        f[from][1]=g[1][1];
    }
}
  
int fa[MAXN],dfn[MAXN],dcnt;
bool onRing[MAXN];
void dfs(int u,int from)
{
    int i,j;dfn[u]=++dcnt;
    for(i=G.G[u];i;i=G.e[i].next)
        if(i^from^1)//判断要走的边是否与来时的边是一条无向边
        {
            int v=G.e[i].to;
            if(!dfn[v])
            {
                fa[v]=u;onRing[u]=false;
                dfs(v,i);
                if(!onRing[u]) T.addEdge2(u,v);
            }
            else
            {
                if(dfn[v]>dfn[u]) continue;
                for(j=u,++newn;j!=fa[v];j=fa[j])
                    T.addEdge2(newn,j),onRing[j]=true;
            }
        }
}
  
int main()
{
    int i,u,v;
    scanf("%d%d",&n,&m);newn=n;
    for(i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        G.addEdge2(u,v);
    }
    dfs(1,0);treeDP(1,0);
    printf("%d\n",std::max(f[1][0],f[1][1]));
}
