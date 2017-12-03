#include<iostream>
#include<cstdio>
#include<cstring>

const int MAXN=5e4+5;

int N,M,Q,ncnt;

int wseq[2*MAXN],wpos[2*MAXN],wcnt;

struct E{int next,to;} e[6*MAXN];int ecnt,cG[MAXN],tG[2*MAXN];
void addEdge(int *G,int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int *G,int u,int v){addEdge(G,u,v);addEdge(G,v,u);}

// tarjan 建圆方树
int fa[2*MAXN],blg[2*MAXN];
int dfn[MAXN],dcnt;
void tarjan(int u)
{
	dfn[u]=++dcnt;
	for(int i=cG[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!dfn[v])
		{
			fa[v]=u;tarjan(v);
			if(!blg[v]) addEdge(tG,u,v);
		}
		else if(v!=fa[u]&&dfn[v]<dfn[u])
		{
			blg[++ncnt]=v;addEdge(tG,v,ncnt);fa[ncnt]=v;
			for(int j=u;j!=v;j=fa[j]) addEdge(tG,ncnt,j),blg[j]=ncnt;
		}
	}
}

//树剖
int sz[2*MAXN],son[2*MAXN];
void dfs1(int u)
{
	sz[u]=1;
	for(int i=tG[u];i;i=e[i].next)
	{
		int v=e[i].to;
		dfs1(v);
		sz[u]+=sz[v];
		if(sz[v]>sz[son[u]]) son[u]=v;
	}
}

int tp[2*MAXN],dis[2*MAXN];
int L[2*MAXN],R[2*MAXN];
int typ[2*MAXN];
void dfs2(int u)
{
	if(!wpos[u]) wseq[wpos[u]=++wcnt]=u;
	else if(u<=N) L[u]=wcnt+1;
	if(!son[u]) {R[u]=wcnt;return;}
	int i,ty;
	if(u>N)
	{
		for(i=tG[u];i;i=e[i].next) dis[e[i].to]=++dis[u];
		L[u]=wcnt+1;
		for(i=tG[u],ty=1+(dis[son[u]]>dis[u]>>1);i;i=e[i].next)
		{
			int v=e[i].to;
			if(v==son[u]) ty^=3;
			else typ[v]=ty,wseq[wpos[v]=++wcnt]=v;
		}
		R[u]=wcnt;
		wseq[wpos[son[u]]=++wcnt]=son[u];
	}
	tp[son[u]]=tp[u];
	dfs2(son[u]);
	for(i=tG[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==son[u]) continue;
		tp[v]=v;dfs2(v);
	}
	if(u<=N) R[u]=wcnt;
}

//线段树
const int rt=1;
struct SEGTN{int l,r,lc,rc;int tot[3],cnt[3];int rev[3];} t[4*MAXN];int tcnt=rt;
void buildTree(int o,int l,int r)
{
	t[o].l=l,t[o].r=r;
	if(l==r) t[o].tot[typ[wseq[l]]]+=wseq[l]<=N;
	else
	{
		int mid=(l+r)>>1;
		t[o].lc=++tcnt;buildTree(t[o].lc,l,mid);
		t[o].rc=++tcnt;buildTree(t[o].rc,mid+1,r);
		for(int i=0;i<3;i++) t[o].tot[i]=t[t[o].lc].tot[i]+t[t[o].rc].tot[i];
	}
	memcpy(t[o].cnt,t[o].tot,sizeof t[o].tot);
}
inline void upd(int o){for(int i=0;i<3;i++) t[o].cnt[i]=t[t[o].lc].cnt[i]+t[t[o].rc].cnt[i];}
inline void psd(int o)
{
	SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];
	for(int i=0;i<3;i++) if(t[o].rev[i])
	{
		lc.rev[i]^=1;lc.cnt[i]=lc.tot[i]-lc.cnt[i];
		rc.rev[i]^=1;rc.cnt[i]=rc.tot[i]-rc.cnt[i];
		t[o].rev[i]=0;
	}
}

void ch(int o,int l,int r,int ty)
{
	if(l<=t[o].l&&t[o].r<=r)
	{
		t[o].rev[0]^=1,t[o].cnt[0]=t[o].tot[0]-t[o].cnt[0];
		if(ty!=2) t[o].rev[1]^=1,t[o].cnt[1]=t[o].tot[1]-t[o].cnt[1];
		if(ty!=1) t[o].rev[2]^=1,t[o].cnt[2]=t[o].tot[2]-t[o].cnt[2];
		return;
	}
	psd(o);
	int mid=(t[o].l+t[o].r)>>1;
	if(l<=mid) ch(t[o].lc,l,r,ty);
	if(r>mid) ch(t[o].rc,l,r,ty);
	upd(o);
}
inline void mdf(int l,int r,int ty){ch(rt,l,r,ty);}
inline void mdf(int p,int ty){ch(rt,p,p,ty);}

int calC(int o,int l,int r)
{
	if(l<=t[o].l&&t[o].r<=r) return t[o].cnt[0]+t[o].cnt[1]+t[o].cnt[2];
	psd(o);
	int mid=(t[o].l+t[o].r)>>1;
	if(l<=mid&&r>mid) return calC(t[o].lc,l,r)+calC(t[o].rc,l,r);
	if(l<=mid) return calC(t[o].lc,l,r);
	return calC(t[o].rc,l,r);
}
inline int qry(int l,int r){return calC(rt,l,r);}
inline int qry(int p){return calC(rt,p,p);}

//主操作
void reverse(int u,int ty)
{
	while(u)
	{
		if(tp[u]==u)
		{
			if(blg[u])
			{
				if((dis[u]<=dis[blg[u]]>>1)==(ty==1))
				{
					mdf(L[blg[u]],wpos[u],0);
					if(dis[son[blg[u]]]<dis[u]) mdf(wpos[son[blg[u]]],0);
				}
				else
				{
					mdf(wpos[u],R[blg[u]],0);
					if(dis[son[blg[u]]]>dis[u]) mdf(wpos[son[blg[u]]],0);
				}
				u=blg[blg[u]];
			}
			else mdf(wpos[u],ty),u=fa[u];
		}
		else if(tp[u]<=N&&blg[tp[u]]) mdf(wpos[son[tp[u]]],wpos[u],ty),u=tp[u];
		else mdf(tp[u]<=N?wpos[tp[u]]:L[tp[u]],wpos[u],ty),u=fa[tp[u]];
	}
}

int query(int u)
{
	int res;
	if(!blg[u]||u==son[blg[u]]) res=qry(wpos[u],R[u]);
	else
	{
		res=qry(wpos[u]);
		if(L[u]<=R[u]) res+=qry(L[u],R[u]);
	}
	return res;
}

int main()
{
	int i;
	scanf("%d%d%d",&N,&M,&Q);ncnt=N;
	for(i=1;i<=M;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addEdge2(cG,u,v);
	}
	tarjan(1);for(i=1;i<=N;i++) if(blg[i]) fa[i]=blg[i];
	tp[1]=1;dfs1(1);dfs2(1);
	buildTree(rt,1,ncnt);
	while(Q--)
	{
		int opt,p;scanf("%d%d",&opt,&p);
		if(opt<3) reverse(p,opt);
		else printf("%d\n",query(p));
	}
	return 0;
}
