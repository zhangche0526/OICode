#include<iostream>
#include<cstdio>
#include<cmath>
#include<vector>
using std::min;
inline void umn(int &a,int b){a=min(a,b);}
using std::max;
inline void umx(int &a,int b){a=max(a,b);}

const int MAXN=1e5+5;

int N,M;
int val[MAXN];
int fa[MAXN];

struct E{int next,to;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}

class LCA
{
private:
	int dpt[MAXN],dptseq[MAXN<<1],dcnt,pos[MAXN];
	void dfs(int u,int la)
	{
		dptseq[pos[u]=++dcnt]=dpt[u];
		for(int i=G[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(v==la) continue;
			dpt[v]=dpt[u]+1;
			dfs(v,u);
			dptseq[++dcnt]=dpt[u];
		}
	}
	int na[MAXN<<1][20];
	int calLcaDpt(int x,int y)
	{
		int l=pos[x],r=pos[y];
		if(l>r) std::swap(l,r);
		int	k=log2(r-l+1);
		return min(na[l][k],na[r-(1<<k)+1][k]);
	}
public:
	void init()
	{
		dfs(1,0);
		int i,k;
		for(i=1;i<=dcnt;i++) na[i][0]=dptseq[i];
		for(k=1;k<=log2(dcnt);k++)
			for(i=1;i+(1<<k)-1<=dcnt;i++)
				na[i][k]=min(na[i][k-1],na[i+(1<<k-1)][k-1]);
	}
	int calDis(int x,int y)
	{return dpt[x]+dpt[y]-2*calLcaDpt(x,y);}
} lca;

class FT
{
private:
	std::vector<int> na;int n;
	void add(int x,int v){for(++x;x<=n;x+=x&-x) na[x-1]+=v;}
	int sum(int x){int res=0;for(x=min(x+1,n);x;x-=x&-x) res+=na[x-1];return res;}
public:
	void add(int l,int r,int v){add(l,v);add(r+1,-v);}
	int get(int x){return sum(x);}
	FT(){}
	FT(int sz){n=sz;na.resize(n);}
} plus[MAXN],minus[MAXN];

class TDC
{
private:
	bool vis[MAXN];

	int rt,mxv[MAXN],mnv,sz[MAXN];
	void calSz(int u,int la)
	{
		sz[u]=1,mxv[u]=0;
		for(int i=G[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(v==la||vis[v]) continue;
			calSz(v,u);
			sz[u]+=sz[v];
			umx(mxv[u],sz[v]);
		}
	}
	void calRt(int u,int la,int r)
	{
		umx(mxv[u],sz[r]-sz[u]);
		if(mxv[u]<mnv) mnv=mxv[u],rt=u;
		for(int i=G[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(v==la||vis[v]) continue;
			calRt(v,u,r);
		}
	}
	int findRt(int u){rt=0,mnv=N;calSz(u,0);calRt(u,0,u);return rt;}
	void dc(int u,int s)
	{
		vis[u]=true;
		plus[u]=FT(s);
		for(int i=G[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(vis[v]) continue;
			int grt=findRt(v);
			fa[grt]=u;
			minus[grt]=FT(sz[v]+1);
			dc(grt,sz[v]);
		}
	}
public:
	void init(){int grt=findRt(1);dc(grt,N);}
} tdc;

int qry(int x)
{
	int res=plus[x].get(0);
	for(int u=x;fa[u];u=fa[u])
	{
		int d=lca.calDis(fa[u],x);
		res+=plus[fa[u]].get(d);
		res-=minus[u].get(d);
	}
	return res;
}

void mdf(int x,int k,int v)
{
	plus[x].add(0,k,v);
	for(int u=x;fa[u];u=fa[u])
	{
		int d=lca.calDis(fa[u],x);
		if(d>k) continue;
		plus[fa[u]].add(0,k-d,v);
		minus[u].add(0,k-d,v);
	}
}
int main()
{
	int i;scanf("%d%d",&N,&M);
	for(i=1;i<N;i++)
	{ 
		int u,v;scanf("%d%d",&u,&v);
		addEdge2(u,v);
	}
	lca.init();
	tdc.init();
	while(M--)
	{
		char opt[10];scanf("%s",opt);
		if(opt[0]=='M')
		{
			int x,k,v;scanf("%d%d%d",&x,&k,&v);
			mdf(x,k,v);
		}
		else
		{
			int x;scanf("%d",&x);
			printf("%d\n",qry(x));
		}
	}
	return 0;
}
