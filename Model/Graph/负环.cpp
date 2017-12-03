#include<iostream>
#include<cstdio>
#include<cstring>

const int MAXN=2e5+5,MAXM=2e5+5;

int n,m;

struct E{int next,to,val;} e[MAXM<<1];int ecnt,G[MAXN];
void addEdge(int u,int v,int w){e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;}

bool vis[MAXN];int dis[MAXN];

bool dfs(int u)
{
    vis[u]=true;
    for(int i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(dis[v]>dis[u]+e[i].val)
        {
            if(vis[v]) return true;
            dis[v]=dis[u]+e[i].val;
            if(dfs(v)) return true;
        }
    }
    vis[u]=false;
    return false;
}

bool chk()
{
    memset(dis,0,sizeof dis);memset(vis,false,sizeof vis);
    for(int i=1;i<=n;i++) if(dfs(i)) return true;
    return false;
}

int main()
{
    int T;scanf("%d",&T);
    while(T--)
    {
        memset(G,0,sizeof G);ecnt=0;
        int i;scanf("%d%d",&n,&m);
        for(i=1;i<=m;i++) 
        {
            int u,v,w;scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            if(w>=0) addEdge(v,u,w);
        }
        if(chk()) puts("YE5");
        else puts("N0");
    }
    return 0;
}
