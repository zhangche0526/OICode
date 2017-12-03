#include<cstdio>
#include<cmath>

const int MAXN=1000005;

int N,M,S;
int anc[MAXN][20],dpt[MAXN];

struct E{int to,next;} e[MAXN];int ecnt,G[MAXN];
void addEdge(int u, int v){e[++ecnt]=(E){v,G[u]};G[u]=ecnt;}

void dfs(int u,int ln)
{
    for(int i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==ln) continue;
        dpt[v]=dpt[u]+1;
        anc[v][0]=u;
        dfs(v,u);
    }
}

void initLCA()
{
    for(int i=1;(1<<i)<=N;i++)
        for(int j=1;j<=N;j++)
            anc[j][i]=anc[anc[j][i-1]][i-1];
}

int calLCA(int x, int y)
{
    int i;
    if(dpt[x]<dpt[y]) std::swap(x,y);
    int maxlogn=std::floor(std::log(N)/std::log(2));
    for(i=maxlogn;i>=0;i--)
        if(dpt[x]-(1<<i)>=dpt[y])
            x=anc[x][i];
    if(x==y) return x;
    for(i=maxlogn;i>=0;i--)
        if(anc[x][i]!=anc[y][i])
            x=anc[x][i],y=anc[y][i];
    return anc[x][0];
}

int main()
{
    scanf("%d%d%d",&N,&M,&S);
    for(int i=1;i<N;i++)
    {
        int u,v;scanf("%d%d",&u,&v);
        addEdge(u,v);addEdge(v,u);
    }
    dfs(S,0);
    initLCA();
    for(int i=1;i<=M;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        printf("%d\n",getlca(a,b));
    }
    return 0;
}
