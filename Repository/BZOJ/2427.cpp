#include<iostream>
#include<cstdio>
#include<stack>

const int MAXN=105,MAXE=MAXN*MAXN,MAXM=505;

int N,M;

class CFS
{
    public:
        struct E{int next,fr,to;} e[MAXM];int ecnt,G[MAXN];
        void addEdge(int u,int v){e[++ecnt]=(E){G[u],u,v};G[u]=ecnt;}
} G1,G2;

int w[MAXN],val[MAXN];

struct S{int w,val;} scc[MAXN];int scnt;

std::stack<int> st;bool inSt[MAXN];
int dfn[MAXN],dcnt,low[MAXN];

int belong[MAXN];
void tarjan(int u)
{
    dfn[u]=low[u]=++dcnt;
    st.push(u);inSt[u]=true;
    for(int i=G1.G[u];i;i=G1.e[i].next)
    {
        int v=G1.e[i].to;
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=std::min(low[u],low[v]);
        }else if(inSt[v])    
            low[u]=std::min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u])
    {
        ++scnt;
        int t;
        do
        {
            t=st.top();st.pop();
            inSt[t]=false;
            belong[t]=scnt;
            scc[scnt].w+=w[t],scc[scnt].val+=val[t];
        }
        while(t!=u);
    }
}

bool hasInDgr[MAXN];

inline void reBuild()
{
    int i;
    for(i=1;i<=G1.ecnt;i++)
        if(belong[G1.e[i].fr]!=belong[G1.e[i].to])
        {
            G2.addEdge(belong[G1.e[i].fr],belong[G1.e[i].to]);
            hasInDgr[belong[G1.e[i].to]]=true;
        }
}

int f[MAXN][MAXM];

void dp(int u)
{
    int i,j,k;
    for(i=G2.G[u];i;i=G2.e[i].next)
    {
        int v=G2.e[i].to;
        dp(v);
        for(j=M-scc[u].w;j>=0;j--)
            for(k=0;k<=j;k++)
                f[u][j]=std::max(f[u][j],f[u][k]+f[v][j-k]);
    }
    for(i=M;i>=0;i--)
        if(i>=scc[u].w) f[u][i]=f[u][i-scc[u].w]+scc[u].val;
        else f[u][i]=0;
}

int main()
{
    int i;
    scanf("%d%d",&N,&M);
    for(i=1;i<=N;i++) scanf("%d",w+i);
    for(i=1;i<=N;i++) scanf("%d",val+i);
    for(i=1;i<=N;i++)
    {
        int k;scanf("%d",&k);
        if(k==0) continue;
        G1.addEdge(k,i);
    }
    for(i=1;i<=N;i++)
        if(!dfn[i]) tarjan(i);
    reBuild();
    int rt=scnt+1;
    for(i=1;i<=scnt;i++)
        if(!hasInDgr[i])
        {
            hasInDgr[i]=true;
            G2.addEdge(rt,i);
        }
    dp(rt);
    printf("%d\n",f[rt][M]);
    return 0;
}
