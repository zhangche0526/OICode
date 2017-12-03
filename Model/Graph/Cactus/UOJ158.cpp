#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<queue>
#include<set>
#define md double
#define LL long long
#define LLD "%lld"
using namespace std;
const int N=2e5+100;
const int inf=2147483647;
int gi()
{
	int w=0;
	bool q=1;
	char c=getchar();
	while ((c<'0'||c>'9') && c!='-') c=getchar();
	if (c=='-') q=0,c=getchar();
	while (c>='0'&&c <= '9') w=w*10+c-'0',c=getchar();
	return q? w:-w;
}
int head[N],next[N<<1],to[N<<1],tot;
int fa[N],n,dis[N],rt[N],scc,in[N],col[N];
int siz[N],son[N],top[N],l[N],r[N],dfn[N],sa[N],R[N],L[N];
int all[N<<2][3],c[N<<2][3];bool tag[N<<2][3];
#define lc (i<<1)
#define rc (i<<1|1)
inline void build(int i,int l,int r) {
	if (l==r) { if (sa[l]<=n) all[i][col[sa[l]]]++; }
	else {
		int m=(l+r)>>1;
		build(lc,l,m);build(rc,m+1,r);
		all[i][0]=all[lc][0]+all[rc][0];all[i][1]=all[lc][1]+all[rc][1];all[i][2]=all[lc][2]+all[rc][2];
	}
	c[i][0]=all[i][0],c[i][1]=all[i][1],c[i][2]=all[i][2];
}
#define pushdown(i) for (m=0;m<3;m++) if (tag[i][m]) tag[lc][m]^=1,c[lc][m]=all[lc][m]-c[lc][m],tag[rc][m]^=1,c[rc][m]=all[rc][m]-c[rc][m],tag[i][m]=0;
inline void modify(int i,int l,int r,int L,int R,int p) {
	if (L<=l&&r<=R) {
		tag[i][0]^=1;c[i][0]=all[i][0]-c[i][0];
		if (p!=2) tag[i][1]^=1,c[i][1]=all[i][1]-c[i][1];
		if (p!=1) tag[i][2]^=1,c[i][2]=all[i][2]-c[i][2];
		return;
	}
	int m;pushdown(i);m=(l+r)>>1;
	if (L<=m) modify(lc,l,m,L,R,p);
	if (m<R) modify(rc,m+1,r,L,R,p);
	c[i][0]=c[lc][0]+c[rc][0];c[i][1]=c[lc][1]+c[rc][1];c[i][2]=c[lc][2]+c[rc][2];
}
inline int query(int i,int l,int r,int L,int R) {
	if (L<=l&&r<=R) return c[i][0]+c[i][1]+c[i][2];
	int m;pushdown(i);m=(l+r)>>1;
	if (R<=m) return query(lc,l,m,L,R);
	if (m<L) return query(rc,m+1,r,L,R);
	return query(lc,l,m,L,R)+query(rc,m+1,r,L,R);
}
namespace tree{
	int head[N],next[N<<1],to[N<<1],tot;
	inline void link(int a,int b) { to[++tot]=b,next[tot]=head[a],head[a]=tot; }
	inline void dfs1(int k) {
		siz[k]=1;
		for (int i=head[k];i;i=next[i]) {
			dfs1(to[i]);siz[k]+=siz[to[i]];
			if (siz[to[i]]>siz[son[k]]) son[k]=to[i];
		}
	}
	inline void dfs2(int k) {
		if (!dfn[k]) sa[dfn[k]=++tot]=k; else if (k<=n) L[k]=tot+1; if (!son[k]) { R[k]=tot; return; }int i,tp;
		if (k>n) {
			for (i=head[k];i;i=next[i]) dis[to[i]]=++dis[k];L[k]=tot+1;
			for (i=head[k],tp=1+(dis[son[k]]>dis[k]>>1);i;i=next[i]) if (to[i]==son[k]) tp^=3; else col[to[i]]=tp,sa[dfn[to[i]]=++tot]=to[i];R[k]=tot;
			sa[dfn[son[k]]=++tot]=son[k];
		}
		top[son[k]]=top[k];dfs2(son[k]);
		for (i=head[k];i;i=next[i]) if (to[i]!=son[k]) top[to[i]]=to[i],dfs2(to[i]);
		if (k<=n) R[k]=tot;
	}
	inline void rev(int k,int p) {
		while (k)
			if (top[k]==k)
				if (rt[k]) {
					if ((dis[k]<=dis[rt[k]]>>1)==(p==1)) {
						modify(1,1,scc,L[rt[k]],dfn[k],0);
						if (dis[son[rt[k]]]<dis[k]) modify(1,1,scc,dfn[son[rt[k]]],dfn[son[rt[k]]],0);
					}
					else {
						modify(1,1,scc,dfn[k],R[rt[k]],0);
						if (dis[son[rt[k]]]>dis[k]) modify(1,1,scc,dfn[son[rt[k]]],dfn[son[rt[k]]],0);
					}
					k=rt[rt[k]];
				}
				else modify(1,1,scc,dfn[k],dfn[k],p),k=fa[k];
			else if (top[k]<=n&&rt[top[k]]) modify(1,1,scc,dfn[son[top[k]]],dfn[k],p),k=top[k];
			else modify(1,1,scc,top[k]<=n?dfn[top[k]]:L[top[k]],dfn[k],p),k=fa[top[k]];
	}
	inline int ask(int k) { return !rt[k]||k==son[rt[k]]?query(1,1,scc,dfn[k],R[k]):query(1,1,scc,dfn[k],dfn[k])+(L[k]<=R[k]?query(1,1,scc,L[k],R[k]):0); }
}
inline void dfs(int k) {
	dfn[k]=++tot;
	for (int i=head[k],t,p;i;i=next[i])
		if (!dfn[to[i]]) {
			fa[to[i]]=k,dfs(to[i]);
			if (!rt[to[i]]) tree::link(k,to[i]);
		}
		else if (to[i]!=fa[k]&&dfn[to[i]]<dfn[k]) {
			rt[p=++scc]=to[i];tree::link(to[i],scc);fa[scc]=to[i];
			for (t=k;t!=to[i];t=fa[p=t]) l[t]=fa[t],r[t]=p,tree::link(scc,t),rt[t]=scc;
			l[scc]=p,r[scc]=k;
		}
}
int main()
{
	//freopen("cactus.in","r",stdin);
	//freopen("cactus.out","w",stdout);
	n=scc=gi();int m=gi(),Q=gi(),k,tot=0,a,b;
	while (m--) {
		a=gi(),b=gi();
		to[++tot]=b,next[tot]=head[a],head[a]=tot;
		to[++tot]=a,next[tot]=head[b],head[b]=tot;
	}
	dfs(1);for (k=1;k<=n;dfn[k++]=0) if (rt[k]) fa[k]=rt[k];
	top[1]=1;tree::tot=0;tree::dfs1(1);
	tree::dfs2(1);
	build(1,1,scc);
	while (Q--) {
		if ((k=gi())==3) printf("%d\n",tree::ask(gi()));
		else tree::rev(gi(),k);
	}	
	return 0;
}
