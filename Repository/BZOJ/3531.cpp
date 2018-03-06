#include<iostream>
#include<cstdio>
typedef long long ll;
const int MAXN=1e5+5,INF=~0U>>1;

int N,M;
int na[MAXN],typ[MAXN];
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

int rt[MAXN];
struct SEGTN{int l,r,lc,rc;int sum,mx;} t[MAXN*40];int tcnt;
void upd(int o)
{
	t[o].sum=t[t[o].lc].sum+t[t[o].rc].sum;
	t[o].mx=std::max(t[t[o].lc].mx,t[t[o].rc].mx);
}
void chCh(int &o,int l,int r,int p,int v)
{
	if(!o) o=++tcnt,t[o].l=l,t[o].r=r;
	if(l==r){t[o].sum=t[o].mx=v;return;}
	int mid=l+r>>1;
	if(p<=mid) chCh(t[o].lc,l,mid,p,v);
	else chCh(t[o].rc,mid+1,r,p,v);
	upd(o);
}
int calSum(int o,int l,int r)
{
    if(!o) return 0;
    if(l<=t[o].l&&t[o].r<=r) return t[o].sum;
    int mid=t[o].l+t[o].r>>1;
    int res=0;
    if(l<=mid) res+=calSum(t[o].lc,l,r);
    if(r>mid) res+=calSum(t[o].rc,l,r);
    return res;
}
int calMx(int o,int l,int r)
{
    if(!o) return 0;
	if(l<=t[o].l&&t[o].r<=r) return t[o].mx;
	int mid=t[o].l+t[o].r>>1;
	int lmx=-INF,rmx=-INF;
	if(l<=mid) lmx=calMx(t[o].lc,l,r);
	if(r>mid) rmx=calMx(t[o].rc,l,r);
	return std::max(lmx,rmx);
}
void changeType(int p,int c)
{
    chCh(rt[typ[p]],1,N,p,0);
    typ[p]=c;
    chCh(rt[typ[p]],1,N,p,na[p]);
}
int chainSum(int t,int x,int y)
{
    int res=0;
    while(tp[x]!=tp[y])
    {
        if(dpt[tp[x]]<dpt[tp[y]]) std::swap(x,y);
        res+=calSum(rt[t],w[tp[x]],w[x]);
        x=fa[tp[x]];
    }
    if(w[x]>w[y]) std::swap(x,y);
    res+=calSum(rt[t],w[x],w[y]);
    return res;
} 
int chainMx(int t,int x,int y)
{
	int res=-INF;
	while(tp[x]!=tp[y])
	{
		if(dpt[tp[x]]<dpt[tp[y]]) std::swap(x,y);
		res=std::max(res,calMx(rt[t],w[tp[x]],w[x]));
		x=fa[tp[x]];
	}
	if(w[x]>w[y]) std::swap(x,y);
	res=std::max(res,calMx(rt[t],w[x],w[y]));
	return res;
}

int tmp[MAXN][2];
int main()
{
    int i;
    scanf("%d%d",&N,&M);
    for(i=1;i<=N;i++) scanf("%d%d",&tmp[i][0],&tmp[i][1]);
    int u,v;
    for(i=1;i<N;i++) scanf("%d%d",&u,&v),addEdge2(u,v);
    dpt[1]=1;dfs1(1);
    tp[1]=1,w[1]=++wcnt;dfs2(1);
    for(i=1;i<=N;i++) na[w[i]]=tmp[i][0],typ[w[i]]=tmp[i][1];
    for(i=1;i<=N;i++)
		chCh(rt[typ[w[i]]],1,N,w[i],na[w[i]]);
    while(M--)
    {
        char opt[10];int x,y;
        scanf("%s%d%d",opt,&x,&y);
        if(opt[0]=='C')
        {
			if(opt[1]=='C') changeType(w[x],y);
			else chCh(rt[typ[w[x]]],1,N,w[x],y),na[w[x]]=y;
        }else 
        {
			if(opt[1]=='S') printf("%d\n",chainSum(typ[w[x]],x,y));
			else printf("%d\n",chainMx(typ[w[x]],x,y));
        }
    }
    return 0;
}
