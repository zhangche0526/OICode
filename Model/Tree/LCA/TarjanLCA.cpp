#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN=1000005;

int N,M,S;

//CFS
struct E{int to,next;} e[MAXN];int ecnt,G[MAXN];
void addEdge(int u,int v)
{e[++ecnt]=(E){v,G[u]};G[u]=ecnt;}

//UFS
int fa[MAXN];
inline void initUFS()
{for(int i=1;i<=N;i++) fa[i]=i;}
int getFa(int x)
{return fa[x]==x?fa[x]:fa[x]=getFa(fa[x]);}

struct A{int to,id,next;} ask[MAXN];int acnt,hd[MAXN];
void addAsk(int x,int y,int z)
{ask[++acnt]=(A){y,z,hd[x]};hd[x]=acnt;}

int ans[MAXN],vis[MAXN];
void calLCA(int u)
{
    int i;vis[u]=true;
    for(i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(!vis[v])
        {
            calLCA(v);
            fa[v]=u;
        }
    }
    for(i=hd[u];i;i=ask[i].next)
    {
        int v=ask[i].to,id=ask[i].id;
        if(vis[v]) ans[id]=getFa(v);
    }
}

int main()
{
    scanf("%d%d%d",&N,&M,&S);
    int i;
    for(i=1;i<N;i++)
    {
        int u,v;scanf("%d%d",&u,&v);
        addEdge(u,v);addEdge(v,u);
    }
    for(i=1;i<=M;i++)
    {
        int x,y;scanf("%d%d",&x,&y);
        addAsk(x,y,i);addAsk(y,x,i);
    }
    initUFS();
    calLCA(S);
    for(i=1;i<=M;i++)
        printf("%d\n",ans[i]);
    return 0;
}
