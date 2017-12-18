#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int MAXN=3e5+5;

int N,M,Q;

struct E{int next,to;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){if(u==v) return;e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}

int dfn[MAXN],dcnt;
bool cmp(int a,int b){return dfn[a]<dfn[b];}
int dpt[MAXN],sz[MAXN],anc[MAXN][20];
void dfs(int u)
{
	int i;dfn[u]=++dcnt,sz[u]=1;
	for(i=1;(1<<i)<=dpt[u];i++)
		anc[u][i]=anc[anc[u][i-1]][i-1];
	for(i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==anc[u][0]) continue;
		dpt[v]=dpt[u]+1,anc[v][0]=u;
		dfs(v);
		sz[u]+=sz[v];
	}
}

int calLCA(int x,int y)
{
	int i;if(dpt[x]<dpt[y]) std::swap(x,y);
	for(i=19;i>=0;i--)
		if(dpt[x]-(1<<i)>=dpt[y])
			x=anc[x][i];
	if(x==y) return x;
	for(i=19;i>=0;i--)
		if(anc[x][i]!=anc[y][i])
			x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

int seq[MAXN],sseq[MAXN];
int st[MAXN],tp;
void buildTree()
{
	int i;ecnt=0;
	std::copy(seq+1,seq+1+M,sseq+1);
	std::sort(sseq+1,sseq+1+M,cmp);
	st[tp=1]=1;
	for(i=1;i<=M;i++)
	{
		int lca=calLCA(sseq[i],st[tp]);
		while(dpt[st[tp-1]]>dpt[lca]) {addEdge(st[tp-1],st[tp]);tp--;}
		addEdge(lca,st[tp]);tp--;
		if(st[tp]!=lca) st[++tp]=lca;
		if(st[tp]!=sseq[i]) st[++tp]=sseq[i];
	}
	while(--tp) addEdge(st[tp],st[tp+1]);
}

inline int calDis(int x,int y){return dpt[x]+dpt[y]-2*dpt[calLCA(x,y)];}

int blg[MAXN],lst[MAXN],lcnt,rst[MAXN];
void dfs1(int u)
{
	lst[++lcnt]=u;rst[u]=sz[u];
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		dfs1(v);if(!blg[v]) continue;
		if(!blg[u]){blg[u]=blg[v];continue;}
		int dv=calDis(u,blg[v]),du=calDis(u,blg[u]);
		if(dv<du||(dv==du&&blg[v]<blg[u])) blg[u]=blg[v];
	}
}

void dfs2(int u)
{
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!blg[v]) blg[v]=blg[u];
		else
		{
			int du=calDis(v,blg[u]),dv=calDis(v,blg[v]);
			if(du<dv||(du==dv&&blg[u]<blg[v])) blg[v]=blg[u];
		}
		dfs2(v);
	}
}

int ans[MAXN];
void dscs(int fa,int u)
{
	int i,son=u,mid=u;
	for(i=19;i>=0;i--)
		if(dpt[son]-(1<<i)>dpt[fa])
			son=anc[son][i];
	rst[fa]-=sz[son];
	if(blg[fa]==blg[u]) {ans[blg[fa]]+=sz[son]-sz[u];return;}
	for(i=19;i>=0;i--)
	{
		int nxt=anc[mid][i];if(dpt[nxt]<=dpt[fa]) continue;
		int df=calDis(nxt,blg[fa]),du=calDis(nxt,blg[u]);
		if(du<df||(du==df&&blg[u]<blg[fa])) mid=nxt;
	}
	ans[blg[fa]]+=sz[son]-sz[mid];
	ans[blg[u]]+=sz[mid]-sz[u];
}

const int rt=1;
int main()
{
	int i;
	scanf("%d",&N);
	for(i=1;i<N;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addEdge2(u,v);
	}
	dfs(rt);
	memset(G,0,sizeof G);
	scanf("%d",&Q);
	while(Q--)
	{
		scanf("%d",&M);lcnt=0;
		for(i=1;i<=M;i++) scanf("%d",seq+i);
		buildTree();
		for(i=1;i<=M;i++) blg[seq[i]]=seq[i];
		dfs1(rt);
		dfs2(rt);
		for(int p=1;p<=lcnt;p++)
			for(i=G[lst[p]];i;i=e[i].next)
				dscs(lst[p],e[i].to);
		for(i=1;i<=lcnt;i++) ans[blg[lst[i]]]+=rst[lst[i]];
		for(i=1;i<=M;i++) printf("%d ",ans[seq[i]]);puts("");
		for(i=1;i<=lcnt;i++) ans[lst[i]]=rst[lst[i]]=G[lst[i]]=blg[lst[i]]=0;
	}
	return 0;
}
/*
10 
2 1 
3 2 
4 3 
5 4 
6 1 
7 3 
8 3 
9 4 
10 1 
1
4 
8 7 10 3
*/
