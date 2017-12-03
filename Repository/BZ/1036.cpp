/**************************************************************
    Problem: 1036
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:2880 ms
    Memory:6844 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
typedef long long ll;
const int MAXN=3e4+5,INF=~0U>>1;
 
int N,Q;
int na[MAXN];
struct E{int next,to;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v),addEdge(v,u);}
 
int son[MAXN],fa[MAXN],sz[MAXN],dpt[MAXN];
void dfs1(int u)
{
    sz[u]=1;
    for(int i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==fa[u]) continue;
        fa[v]=u,dpt[v]=dpt[u]+1;
        dfs1(v);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]]) son[u]=v;
    }
}
 
int w[MAXN],wcnt,tp[MAXN];
void dfs2(int u)
{
    int v=son[u];if(!v) return;
    tp[v]=tp[u],w[v]=++wcnt;
    dfs2(v);
    for(int i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==fa[u]||v==son[u]) continue;
        tp[v]=v,w[v]=++wcnt;
        dfs2(v);
    }
}
 
const int rt=1;
struct SEGTN{int l,r,lc,rc;int sum,mx;} t[MAXN<<2];int tcnt=rt;
void upd(int o)
{
    t[o].sum=t[t[o].lc].sum+t[t[o].rc].sum;
    t[o].mx=std::max(t[t[o].lc].mx,t[t[o].rc].mx);
}
void buildTree(int o,int l,int r)
{
    t[o].l=l,t[o].r=r;
    if(l==r) {t[o].sum=t[o].mx=na[l];return;}
    int mid=(l+r)>>1;
    t[o].lc=++tcnt;buildTree(t[o].lc,l,mid);
    t[o].rc=++tcnt;buildTree(t[o].rc,mid+1,r);
    upd(o);
}
void change(int o,int p,int v)
{
    if(t[o].l==t[o].r&&t[o].l==p)
    {
        t[o].sum=t[o].mx=v;
        return;
    }
    int mid=(t[o].l+t[o].r)>>1;
    if(p<=mid) change(t[o].lc,p,v);
    else change(t[o].rc,p,v);
    upd(o);
}
int calSum(int o,int l,int r)
{
    if(l<=t[o].l&&t[o].r<=r) return t[o].sum;
    int mid=(t[o].l+t[o].r)>>1;
    int res=0;
    if(l<=mid) res+=calSum(t[o].lc,l,r);
    if(r>mid) res+=calSum(t[o].rc,l,r);
    return res;
}
int calMx(int o,int l,int r)
{
    if(l<=t[o].l&&t[o].r<=r) return t[o].mx;
    int mid=(t[o].l+t[o].r)>>1;
    int lmx=-INF,rmx=-INF;
    if(l<=mid) lmx=calMx(t[o].lc,l,r);
    if(r>mid) rmx=calMx(t[o].rc,l,r);
    return std::max(lmx,rmx);
}
int chainSum(int x,int y)
{
    int res=0;
    while(tp[x]!=tp[y])
    {
        if(dpt[tp[x]]<dpt[tp[y]]) std::swap(x,y);
        res+=calSum(rt,w[tp[x]],w[x]);
        x=fa[tp[x]];
    }
    if(w[x]>w[y]) std::swap(x,y);
    res+=calSum(rt,w[x],w[y]);
    return res;
}
int chainMx(int x,int y)
{
    int res=-INF;
    while(tp[x]!=tp[y])
    {
        if(dpt[tp[x]]<dpt[tp[y]]) std::swap(x,y);
        res=std::max(res,calMx(rt,w[tp[x]],w[x]));
        x=fa[tp[x]];
    }
    if(w[x]>w[y]) std::swap(x,y);
    res=std::max(res,calMx(rt,w[x],w[y]));
    return res;
}
 
char opt[10];
int main()
{
    int i;
    scanf("%d",&N);
    int u,v;
    for(i=1;i<N;i++) scanf("%d%d",&u,&v),addEdge2(u,v);
    dpt[1]=1;dfs1(1);
    tp[1]=1,w[1]=++wcnt;dfs2(1);
    for(i=1;i<=N;i++) scanf("%d",&na[w[i]]);
    buildTree(rt,1,N);
    scanf("%d",&Q);
    while(Q--)
    {
        scanf("%s%d%d",opt,&u,&v);
        if(opt[0]=='C') change(rt,w[u],v);
        else
        {
            if(opt[1]=='S') printf("%d\n",chainSum(u,v));
            else printf("%d\n",chainMx(u,v));
        }
    }
    return 0;
}
