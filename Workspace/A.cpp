#include<iostream>
#include<cstdio>
using std::max;
inline void umx(int &a,int b){a=max(a,b);}
const int MAXN=1e5+5;

int n;
int a[MAXN];

struct E{int next,to;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}

int dpt[MAXN],D,sz[MAXN];
int wpos[MAXN],wseq[MAXN],wcnt;
void predfs(int u,int la)
{
	sz[u]=1;
	wseq[wpos[u]=++wcnt]=u;
	umx(D,dpt[u]);
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la) continue;
		dpt[v]=dpt[u]+1;
		predfs(v,u);
		sz[u]+=sz[v];
	}
}

struct CMT{int lc,rc,sz;} t[MAXN*20];int tcnt,rt[MAXN];
void ist(int &o,int la,int l,int r,int p,int v)
{
	t[o=++tcnt]=t[la];t[o].sz+=v;
	if(l==r) return;
	int mid=l+r>>1;
	if(p<=mid) ist(t[o].lc,t[la].lc,l,mid,p,v);
	else ist(t[o].rc,t[la].rc,mid+1,r,p,v);
}
inline void ist(int p,int v,int c){ist(rt[p],rt[p-1],0,D,v,c);}
int qry(int o,int la,int l,int r,int p)
{
	if(p>r) return 0;
	if(l==r) return t[o].sz-t[la].sz;
	int mid=l+r>>1;
	if(p<=mid) return qry(t[o].lc,t[la].lc,l,mid,p);
	else return qry(t[o].rc,t[la].rc,mid+1,r,p);
}
inline int qry(int l,int r,int v){return qry(rt[r],rt[l-1],0,D,v);}

inline void buildTree()
{
	for(int i=1;i<=n;i++)
		ist(i,dpt[wseq[i]],a[wseq[i]]);
}

int ans[MAXN];
void dfs(int u,int la)
{
	ans[u]=ans[la]+qry(wpos[u],wpos[u]+sz[u]-1,dpt[u]*2);
	if(dpt[u]) ans[u]+=qry(wpos[u],wpos[u]+sz[u]-1,dpt[u]*2-1);
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la) continue;
		dfs(v,u);
	}
}


int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	int i;scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",a+i);
	for(i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addEdge2(u,v);
	}
	predfs(1,0);
	buildTree();
	dfs(1,0);
	for(i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}
