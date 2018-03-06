#include<iostream>
#include<cstdio>
typedef long long ll;
const int MAXN=1e5+5;

int N,M;
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
struct SEGTN
{
	int l,r,lc,rc;
	int sum,tag,clrL,clrR;
	SEGTN(){tag=clrL=clrR=-1;}
} t[MAXN<<2];
int tcnt=rt;
int clrL,clrR;
void upd(int o)
{
	t[o].sum=t[t[o].lc].sum+t[t[o].rc].sum;
	if(t[t[o].lc].clrR==t[t[o].rc].clrL) t[o].sum--;
	t[o].clrL=t[t[o].lc].clrL,t[o].clrR=t[t[o].rc].clrR;
}
void pushdown(int o)
{
    SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];int &tag=t[o].tag;
    if(~tag)
    {
        lc.sum=1,lc.clrL=lc.clrR=tag,lc.tag=tag;
        rc.sum=1,rc.clrL=rc.clrR=tag,rc.tag=tag;
        tag=-1;
    }
}
void buildTree(int o,int l,int r)
{
    t[o].l=l,t[o].r=r;
    if(l==r)
    {
		t[o].sum=1,t[o].clrL=t[o].clrR=na[l];
		return;
	}
    int mid=l+r>>1;
    t[o].lc=++tcnt;buildTree(t[o].lc,l,mid);
    t[o].rc=++tcnt;buildTree(t[o].rc,mid+1,r);
    upd(o);
}
void chCh(int o,int l,int r,int v)
{
    if(l<=t[o].l&&t[o].r<=r)
    {
		t[o].sum=1,t[o].clrL=t[o].clrR=v,t[o].tag=v;
        return;
    }
    int mid=t[o].l+t[o].r>>1;
    pushdown(o);
    if(l<=mid) chCh(t[o].lc,l,r,v);
    if(r>mid) chCh(t[o].rc,l,r,v);
    upd(o);
}
int calSum(int o,int l,int r)
{
	if(t[o].l==l) clrL=t[o].clrL;
	if(t[o].r==r) clrR=t[o].clrR;
    if(l<=t[o].l&&t[o].r<=r) return t[o].sum;
    int mid=t[o].l+t[o].r>>1;
    pushdown(o);
    int res=0,resL=0,resR=0;
    if(l<=mid) resL=calSum(t[o].lc,l,r);
    if(r>mid) resR=calSum(t[o].rc,l,r);
    res=resL+resR;
    if(resL&&resR&&t[t[o].lc].clrR==t[t[o].rc].clrL)
		res--;
    return res;
}
void chainCh(int x,int y,int v)
{
    while(tp[x]!=tp[y])
    {
        if(dpt[tp[x]]<dpt[tp[y]]) std::swap(x,y);
        chCh(rt,w[tp[x]],w[x],v);
        x=fa[tp[x]];
    }
    if(w[x]>w[y]) std::swap(x,y);
    chCh(rt,w[x],w[y],v);
}
int chainSum(int x,int y)
{
    int res=0,clrX=-1,clrY=-1;clrL=clrR=-1;
    while(tp[x]!=tp[y])
    {
        if(dpt[tp[x]]<dpt[tp[y]]) std::swap(x,y),std::swap(clrX,clrY);
        res+=calSum(rt,w[tp[x]],w[x]);
		if(clrR==clrX) res--;
        clrX=clrL;
        x=fa[tp[x]];
    }
    if(w[x]>w[y]) std::swap(x,y),std::swap(clrX,clrY);
    res+=calSum(rt,w[x],w[y]);
    if(clrX==clrL) res--;
    if(clrY==clrR) res--;
    return res;
} 

int tmp[MAXN];
int main()
{
    int i;
    scanf("%d%d",&N,&M);
    for(i=1;i<=N;i++) scanf("%d",&tmp[i]);
    int u,v;
    for(i=1;i<N;i++) scanf("%d%d",&u,&v),addEdge2(u,v);
    dpt[1]=1;dfs1(1);
    tp[1]=1,w[1]=++wcnt;dfs2(1);
    for(i=1;i<=N;i++) na[w[i]]=tmp[i];
    buildTree(rt,1,N);
    while(M--)
    {
        char opt[10];int x,y,z;
        scanf("%s%d%d",opt,&x,&y);
        if(opt[0]=='C') scanf("%d",&z),chainCh(x,y,z);
        else printf("%d\n",chainSum(x,y));
    }
    return 0;
}
