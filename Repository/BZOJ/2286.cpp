/**************************************************************
    Problem: 2286
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:8052 ms
    Memory:42320 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
typedef long long ll;
     
const int MAXN=250005;
const ll INF=~0ULL>>1;
     
int read()
{
    int res=0,flag=1;char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') flag=-1;c=getchar();}
    while(c>='0'&&c<='9') {res=res*10+c-'0';c=getchar();}
    return flag*res;
}
     
class CFS
{
    public:
        struct E{int next,to,val;} e[MAXN<<1];int ecnt,G[MAXN];
        void addEdge(int u,int v,int w=0){e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;}
        void addEdge2(int u,int v,int w){addEdge(u,v,w);addEdge(v,u,w);}
} T,VT;
     
int n,m;
int dpt[MAXN],anc[MAXN][20];
int dfn[MAXN],dcnt;
ll minVal[MAXN];
     
void dfs(int u,int la)
{
    dfn[u]=++dcnt;
    for(int i=T.G[u];i;i=T.e[i].next)
    {
        int v=T.e[i].to;
        if(v==la) continue;
        minVal[v]=std::min(minVal[u],(ll)T.e[i].val);
        dpt[v]=dpt[u]+1;
        anc[v][0]=u;
        dfs(v,u);        
    }
}
     
inline void initAnc()
{
    for(int i=1;(1<<i)<=n;i++)
        for(int j=1;j<=n;j++)
            anc[j][i]=anc[anc[j][i-1]][i-1];
}
     
int calLCA(int x,int y)
{
    int i;
    if(dpt[x]<dpt[y]) std::swap(x,y);
    int maxlogn=std::floor(std::log(n)/std::log(2));
    for(i=maxlogn;i>=0;i--)
    {
        if(dpt[x]-(1<<i)>=dpt[y])
            x=anc[x][i];
    }
    if(x==y) return x;
    for(i=maxlogn;i>=0;i--)
    {
        if(anc[x][i]!=anc[y][i])
        {
            x=anc[x][i];
            y=anc[y][i];
        }
    }
    return anc[x][0];
}
     
ll f[MAXN];
void dp(int u)
{
    int i;ll t=0;
    for(i=VT.G[u];i;i=VT.e[i].next)
    {
        int v=VT.e[i].to;
        dp(v);t+=f[v];
    }
    VT.G[u]=0;
    if(t) f[u]=std::min(minVal[u],t);
    else f[u]=minVal[u];
}
     
int h[MAXN];
bool cmp(const int &x,const int &y)
{return dfn[x]<dfn[y];}
int st[MAXN],tp;
ll calc()
{
    int i;
    VT.ecnt=0;
    int K=read();
    for(i=1;i<=K;i++) h[i]=read();
    std::sort(h+1,h+K+1,cmp);
    int tot=0;
    h[++tot]=h[1];
    for(i=2;i<=K;i++)
        if(calLCA(h[tot],h[i])!=h[tot])
            h[++tot]=h[i];
    st[++tp]=1;
    for(i=1;i<=tot;i++)
    {
        int lca=calLCA(h[i],st[tp]);
        while(true)
        {
            if(dpt[lca]>=dpt[st[tp-1]])
            {
                if(lca!=st[tp]) VT.addEdge(lca,st[tp]);tp--;
                if(st[tp]!=lca) st[++tp]=lca;
                break;
            }
            VT.addEdge(st[tp-1],st[tp--]);;
        }
        if(st[tp]!=h[i]) st[++tp]=h[i];
    }
    while(--tp) VT.addEdge(st[tp],st[tp+1]);
    dp(1);
    return f[1];
}
     
int main()
{
    int i;
    n=read();
    for(i=1;i<n;i++)
    {
        int u=read(),v=read(),w=read();
        T.addEdge2(u,v,w);
    }
    minVal[1]=INF;
    dfs(1,0);initAnc();
    m=read();
    while(m--) printf("%lld\n",calc());
}
