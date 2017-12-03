#include<iostream>
#include<cstdio>
typedef long long ll;
const int MAXN=1e5+5;

int N,M,R,P;
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
struct SEGTN{int l,r,lc,rc;int sum,tag;} t[MAXN<<2];int tcnt=rt;
void upd(int o)
{t[o].sum=((ll)t[t[o].lc].sum+(ll)t[t[o].rc].sum)%P;}
void pushdown(int o)
{
    SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];int &tag=t[o].tag;
    if(tag)
    {
        lc.sum=((ll)lc.sum+((ll)(lc.r-lc.l+1)*(ll)tag)%P)%P,lc.tag=((ll)lc.tag+(ll)tag)%P;
        rc.sum=((ll)rc.sum+((ll)(rc.r-rc.l+1)*(ll)tag)%P)%P,rc.tag=((ll)rc.tag+(ll)tag)%P;
        tag=0;
    }
}
void buildTree(int o,int l,int r)
{
    t[o].l=l,t[o].r=r;
    if(l==r) {t[o].sum=na[l];return;}
    int mid=(l+r)>>1;
    t[o].lc=++tcnt;buildTree(t[o].lc,l,mid);
    t[o].rc=++tcnt;buildTree(t[o].rc,mid+1,r);
    upd(o);
}
void chDet(int o,int l,int r,int v)
{
    if(l<=t[o].l&&t[o].r<=r)
    {
        t[o].sum=((ll)t[o].sum+((((ll)t[o].r-(ll)t[o].l+1LL)%P)*(ll)v)%P)%P;
        t[o].tag=((ll)t[o].tag+(ll)v)%P;
        return;
    }
    int mid=(t[o].l+t[o].r)>>1;
    pushdown(o);
    if(l<=mid) chDet(t[o].lc,l,r,v);
    if(r>mid) chDet(t[o].rc,l,r,v);
    upd(o);
}
int calSum(int o,int l,int r)
{
    if(l<=t[o].l&&t[o].r<=r) return t[o].sum;
    int mid=(t[o].l+t[o].r)>>1;
    pushdown(o);
    int res=0;
    if(l<=mid) res=((ll)res+calSum(t[o].lc,l,r))%P;
    if(r>mid) res=((ll)res+calSum(t[o].rc,l,r))%P;
    return res;
}
void chainDet(int x,int y,int v)
{
    while(tp[x]!=tp[y])
    {
        if(dpt[tp[x]]<dpt[tp[y]]) std::swap(x,y);
        chDet(rt,w[tp[x]],w[x],v);
        x=fa[tp[x]];
    }
    if(w[x]>w[y]) std::swap(x,y);
    chDet(rt,w[x],w[y],v);
}
int chainSum(int x,int y)
{
    int res=0;
    while(tp[x]!=tp[y])
    {
        if(dpt[tp[x]]<dpt[tp[y]]) std::swap(x,y);
        res=((ll)res+calSum(rt,w[tp[x]],w[x]))%P;
        x=fa[tp[x]];
    }
    if(w[x]>w[y]) std::swap(x,y);
    res=((ll)res+calSum(rt,w[x],w[y]))%P;
    return res;
} 

void stDet(int x,int v){chDet(rt,w[x],w[x]+sz[x]-1,v);}
int stSum(int x){return calSum(rt,w[x],w[x]+sz[x]-1);}

int tmp[MAXN];
int main()
{
    int i;
    scanf("%d%d%d%d",&N,&M,&R,&P);
    for(i=1;i<=N;i++) scanf("%d",&tmp[i]);
    int u,v;
    for(i=1;i<N;i++) scanf("%d%d",&u,&v),addEdge2(u,v);
    dpt[R]=1;dfs1(R);
    tp[R]=R,w[R]=++wcnt;dfs2(R);
    for(i=1;i<=N;i++) na[w[i]]=tmp[i];
    buildTree(rt,1,N);
    while(M--)
    {
        int opt,x,y,z;
        scanf("%d%d",&opt,&x);
        if(opt==1) scanf("%d%d",&y,&z),chainDet(x,y,z);
        else if(opt==2) scanf("%d",&y),printf("%d\n",chainSum(x,y));
        else if(opt==3) scanf("%d",&y),stDet(x,y);
        else if(opt==4) printf("%d\n",stSum(x));
    }
    return 0;
}
