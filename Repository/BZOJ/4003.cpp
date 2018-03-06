/**************************************************************
    Problem: 4003
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:4864 ms
    Memory:73868 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
typedef long long ll;
 
const int MAXN=3e5+5;
 
int n,m;
 
ll H[MAXN];
int T[MAXN];ll V[MAXN];
int OP[MAXN],ED[MAXN],D[MAXN];
 
struct E{int next,to;} e[MAXN];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
 
struct LT{int lc,rc,d;ll w,det,mul;LT():mul(1){}} t[MAXN];int rt[MAXN];
inline void pushdown(int o)
{
    if(!o) return;
    LT &lc=t[t[o].lc],&rc=t[t[o].rc];
    if(t[o].mul!=1)
    {
        lc.w*=t[o].mul,lc.det*=t[o].mul,lc.mul*=t[o].mul;
        rc.w*=t[o].mul,rc.det*=t[o].mul,rc.mul*=t[o].mul;
        t[o].mul=1;
    }
    if(t[o].det)
    {
        lc.w+=t[o].det,lc.det+=t[o].det;
        rc.w+=t[o].det,rc.det+=t[o].det;
        t[o].det=0;
    }
}
int merge(int x,int y)
{
    if(!x) return y;
    if(!y) return x;
    pushdown(x),pushdown(y);
    if(t[x].w>t[y].w) std::swap(x,y);
    t[x].rc=merge(t[x].rc,y);
    if(t[t[x].lc].d<t[t[x].rc].d) std::swap(t[x].lc,t[x].rc);
    t[x].d=t[t[x].rc].d+1;
    return x;
}
 
int dpt[MAXN];
void dfs(int u)
{
    for(int i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;
        dpt[v]=dpt[u]+1;
        dfs(v);
        if(T[v]) t[rt[v]].w*=V[v],t[rt[v]].det*=V[v],t[rt[v]].mul*=V[v];
        else t[rt[v]].w+=V[v],t[rt[v]].det+=V[v];
        rt[u]=merge(rt[u],rt[v]);
    }
    while(rt[u]&&t[rt[u]].w<H[u])
    {
        D[u]++,ED[rt[u]]=u;
        pushdown(rt[u]);
        rt[u]=merge(t[rt[u]].lc,t[rt[u]].rc);
    }
}
 
int main()
{
    int i;scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++) scanf("%lld",H+i);
    for(i=2;i<=n;i++)
    {
        int f;scanf("%d%d%lld",&f,T+i,V+i);
        addEdge(f,i);
    }
    for(i=1;i<=m;i++)
    {
        scanf("%lld%d",&t[i].w,OP+i);
        rt[OP[i]]=merge(rt[OP[i]],i);
    }
    t[0].d=-1,dpt[1]=1;
    dfs(1);
    for(i=1;i<=n;i++) printf("%d\n",D[i]);
    for(i=1;i<=m;i++) printf("%d\n",dpt[OP[i]]-dpt[ED[i]]);
    return 0;
}
?
